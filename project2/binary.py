import cv2
import numpy as np
import common

def beforeStart(in_path, kernel):
    img = cv2.imread(in_path)
    grayImage = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    ret, temp = cv2.threshold(grayImage, 127, 255, cv2.THRESH_BINARY)

    path = in_path.split('.')
    temp_path = path[0] + "_binary." + path[1]
    cv2.imwrite(temp_path, temp)

    # 得到结构元原点位置
    for i in range(kernel.shape[0]):
        for j in range(kernel.shape[1]):
            if kernel[i, j] == 2.0:
                kernel[i, j] = 1.0
                return temp, kernel, i, j
    return temp, kernel, 0, 0

def dilation_morph(image, kernel, c_i, c_j):
    (m, n) = image.shape
    (k_m, k_n) = kernel.shape
    final = np.pad(image, ((c_i, k_m-c_i-1), (c_j, k_n-c_j-1)), 'constant')
    output = np.zeros(final.shape)

    for i in range(m):
        for j in range(n):
            if image[i, j] == 255:
                temp = final[i: i + k_m, j: j + k_n]
                for p in range(k_m):
                    for q in range(k_n):
                        if temp[p, q] == 255 or kernel[p, q] == 1.0:
                            output[i + p, j + q] = 255
    return output[c_i : final.shape[0]- k_m + c_i + 1, c_j : final.shape[1] - k_n + c_j + 1]

def dilation(in_path, out_path, kernel):
    image, kernel, c_i,  c_j = beforeStart(in_path, kernel)
    output = dilation_morph(image, kernel, c_i, c_j)
    cv2.imwrite(out_path, output)
    return 0

def erosion_morph(image, kernel, c_i, c_j):
    (m, n) = image.shape
    (k_m, k_n) = kernel.shape
    output = np.zeros((m - k_m + 1, n - k_n + 1))

    for i in range(m - k_m + 1):
        for j in range(n - k_n + 1):
            temp = image[i : i + k_m, j : j + k_n]
            erose = True
            for p in range(k_m):
                for q in range(k_n):
                    if kernel[p, q] == 1.0 and temp[p, q] != 255:
                        erose = False
            if erose:
                output[i, j] = 255
    output = np.pad(output, ((c_i, k_m-c_i-1), (c_j, k_n-c_j-1)), 'constant')
    return output

def erosion(in_path, out_path, kernel):
    image, kernel, c_i,  c_j = beforeStart(in_path, kernel)
    output = erosion_morph(image, kernel, c_i, c_j)
    cv2.imwrite(out_path, output)
    return 0

def open(in_path, out_path, kernel):
    image, kernel, c_i,  c_j = beforeStart(in_path, kernel)

    temp = erosion_morph(image, kernel, c_i, c_j)
    output = dilation_morph(temp, kernel, c_i, c_j)
    cv2.imwrite(out_path, output)
    return 0

def close(in_path, out_path, kernel):
    image, kernel, c_i,  c_j = beforeStart(in_path, kernel)
    temp = dilation_morph(image, kernel, c_i, c_j)
    output = erosion_morph(temp, kernel, c_i, c_j)
    cv2.imwrite(out_path, output)
    return 0

def edge_standard(in_path, out_path, kernel):
    image, kernel, c_i, c_j = beforeStart(in_path, kernel)
    external = dilation_morph(image, kernel, c_i, c_j)
    internal = erosion_morph(image, kernel, c_i, c_j)
    output = external - internal
    cv2.imwrite(out_path, output)
    return 0

def edge_internal(in_path, out_path, kernel):
    image, kernel, c_i, c_j = beforeStart(in_path, kernel)
    internal = erosion_morph(image, kernel, c_i, c_j)
    output = image - internal
    cv2.imwrite(out_path, output)
    return 0

def edge_external(in_path, out_path, kernel):
    image, kernel, c_i, c_j = beforeStart(in_path, kernel)
    external = dilation_morph(image, kernel, c_i, c_j)
    output = external - image
    cv2.imwrite(out_path, output)
    return 0

def intersection(image, temp):
    output = np.zeros(temp.shape)
    for i in range(temp.shape[0]):
        for j in range(temp.shape[1]):
            if temp[i, j] == 255 and image[i, j] == 255:
                output[i, j] = 255
    return output

# 就是先膨胀再求交集，递归下去直到最终稳定
def conditional_dilation(in_path, mask_path, out_path, kernel):
    image, kernel, c_i,  c_j = beforeStart(in_path, kernel)

    img = cv2.imread(mask_path)
    grayImage = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    ret, mask = cv2.threshold(grayImage, 127, 255, cv2.THRESH_BINARY)

    temp = dilation_morph(image, kernel, c_i, c_j)
    output = intersection(temp, mask)
    while common.ifEqual(image, output) != True:
        image = output
        temp = dilation_morph(image, kernel, c_i, c_j)
        output = intersection(temp, mask)
    cv2.imwrite(out_path, output)
    return 0

# kernel = np.array([1, 1, 1, 1, 2, 1, 1, 1, 1]).reshape(3, 3)
# conditional_dilation('/home/rsp/chris/2019-hw/cv/homework2/image/1_erosion.jpeg', '/home/rsp/chris/2019-hw/cv/homework2/image/1.jpeg', '/home/rsp/chris/2019-hw/cv/homework2/image/1_con_dilation.jpeg', kernel)

# edge_standard('/home/rsp/chris/2019-hw/cv/homework2/image/1.jpeg', '/home/rsp/chris/2019-hw/cv/homework2/image/1_gray_standard.jpeg', kernel)
# edge_internal('/home/rsp/chris/2019-hw/cv/homework2/image/1.jpeg', '/home/rsp/chris/2019-hw/cv/homework2/image/1_gray_internal.jpeg', kernel)
# edge_external('/home/rsp/chris/2019-hw/cv/homework2/image/1.jpeg', '/home/rsp/chris/2019-hw/cv/homework2/image/1_gray_external.jpeg', kernel)