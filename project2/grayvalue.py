import cv2
import numpy as np
import common

# 浮点数有且只有一个，小数表示原点，整数表示有效值
def beforeStart(in_path, kernel):
    image = cv2.imread(in_path, 0)

    for i in range(kernel.shape[0]):
        for j in range(kernel.shape[1]):
            if kernel[i, j] % 1 != 0:
                kernel[i, j] = kernel[i, j] // 1
                return image, kernel, i, j
    return image, kernel, 0, 0

def dilation_morph(image, kernel, c_i, c_j):
    (m, n) = image.shape
    (k_m, k_n) = kernel.shape
    final = np.pad(image, ((c_i, k_m - c_i - 1), (c_j, k_n - c_j - 1)), 'constant')
    output = np.zeros(image.shape)
    
    for i in range(m):
        for j in range(n):
            temp = final[i: i+k_m, j:j+k_n]
            output[i, j] = temp[0,0]*kernel[0,0]
            for p in range(k_m):
                for q in range(k_n):
                    if output[i, j] < temp[p, q]*kernel[p, q]:
                        output[i, j] = temp[p, q] * kernel[p, q]
    return output

def dilation(in_path, out_path, kernel):
    image, kernel, c_i, c_j = beforeStart(in_path, kernel)
    output = dilation_morph(image, kernel, c_i, c_j)
    cv2.imwrite(out_path, output)
    return 0

def erosion_morph(image, kernel, c_i, c_j):
    (m, n) = image.shape
    (k_m, k_n) = kernel.shape
    final = np.pad(image, ((c_i, k_m - c_i - 1), (c_j, k_n - c_j - 1)), 'constant')
    output = np.zeros(image.shape)
    
    for i in range(m):
        for j in range(n):
            temp = final[i: i + k_m, j : j + k_n]
            output[i, j] = temp[0,0]*kernel[0,0]
            for p in range(k_m):
                for q in range(k_n):
                    if output[i, j] > temp[p, q]*kernel[p, q]:
                        output[i, j] = temp[p, q] * kernel[p, q]
    return output

def erosion(in_path, out_path, kernel):
    image, kernel, c_i, c_j = beforeStart(in_path, kernel)
    output = erosion_morph(image, kernel, c_i, c_j)
    cv2.imwrite(out_path, output)
    return 0

def open(in_path, out_path, kernel):
    image, kernel, c_i, c_j = beforeStart(in_path, kernel)
    temp = erosion_morph(image, kernel, c_i, c_j)
    output = dilation_morph(temp, kernel, c_i, c_j)
    cv2.imwrite(out_path, output)
    return 0

def close(in_path, out_path, kernel):
    image, kernel, c_i, c_j = beforeStart(in_path, kernel)
    temp = dilation_morph(image, kernel, c_i, c_j)
    output = erosion_morph(temp, kernel, c_i, c_j)
    cv2.imwrite(out_path, output)
    return 0

def gradient_standard(in_path, out_path, kernel):
    image, kernel, c_i, c_j = beforeStart(in_path, kernel)
    external = dilation_morph(image, kernel, c_i, c_j)
    internal = erosion_morph(image, kernel, c_i, c_j)
    output = 0.5 * (external - internal)
    cv2.imwrite(out_path, output)
    return 0

def gradient_internal(in_path, out_path, kernel):
    image, kernel, c_i, c_j = beforeStart(in_path, kernel)
    internal = erosion_morph(image, kernel, c_i, c_j)
    output = 0.5 * (image - internal)
    cv2.imwrite(out_path, output)
    return 0

def gradient_external(in_path, out_path, kernel):
    image, kernel, c_i, c_j = beforeStart(in_path, kernel)
    external = dilation_morph(image, kernel, c_i, c_j)
    output = 0.5 * (external - image)
    cv2.imwrite(out_path, output)
    return 0

def bottom(image, mask, temp):
    equal = True
    output = np.zeros(image.shape)
    for i in range(output.shape[0]):
        for j in range(output.shape[1]):
            if temp[i, j] < mask[i, j]:
                output[i, j] = temp[i, j]
            else:
                output[i, j] = mask[i, j]
            if image[i, j] != output[i, j]:
                equal = False
    return output, equal

def top(image, mask, temp):
    equal = True
    output = np.zeros(image.shape)
    for i in range(output.shape[0]):
        for j in range(output.shape[1]):
            if temp[i, j] > mask[i, j]:
                output[i, j] = temp[i, j]
            else:
                output[i, j] = mask[i, j]
            if image[i, j] != output[i, j]:
                equal = False
    return output, equal

# 与条件膨胀类似，先给灰度图g作膨胀，然后限制图片不超过f，递归直到g稳定
def reconstruction(in_path, mask_path, out_path, kernel):
    image, kernel, c_i,  c_j = beforeStart(in_path, kernel)

    mask = cv2.imread(mask_path, 0)

    temp = dilation_morph(image, kernel, c_i, c_j)
    output, equal = bottom(image, mask, temp)
    while equal != True:
        image = output
        temp = dilation_morph(image, kernel, c_i, c_j)
        output, equal = bottom(image, mask, temp)
    cv2.imwrite(out_path, output)
    return 0

def obr_recon(in_path, out_path, kernel):
    # 开操作
    open(in_path, out_path, kernel)
    # 重建
    reconstruction(out_path, in_path, out_path, kernel)
    return 0

def cbr_recon(in_path, out_path, kernel):
    # 闭操作
    close(in_path, out_path, kernel)
    # 重建
    reconstruction(out_path, in_path, out_path, kernel)
    return 0

def geodesic_open(in_path, mask_path, out_path, kernel):
    image, kernel, c_i,  c_j = beforeStart(in_path, kernel)
    mask = cv2.imread(mask_path, 0)

    temp = dilation_morph(image, kernel, c_i, c_j)
    output, equal = bottom(image, mask, temp)
    while equal != True:
        image = output
        temp = dilation_morph(image, kernel, c_i, c_j)
        output, equal = bottom(image, mask, temp)
    cv2.imwrite(out_path, output)
    return 0
    
def geodesic_close(in_path, mask_path, out_path, kernel):
    image, kernel, c_i,  c_j = beforeStart(in_path, kernel)
    mask = cv2.imread(mask_path, 0)

    temp = erosion_morph(image, kernel, c_i, c_j)
    output, equal = top(image, mask, temp)
    while equal != True:
        image = output
        temp = erosion_morph(image, kernel, c_i, c_j)
        output, equal = top(image, mask, temp)
    cv2.imwrite(out_path, output)
    return 0

# kernel = np.array([1, 1, 1, 1, 1.1, 1, 1, 1, 1]).reshape(3, 3)
# path = '/home/rsp/chris/2019-hw/cv/homework2/image/'

# obr_recon(path + '5.jpeg', path + '5_obr.jpeg', kernel)
# print('obr ok')
# cbr_recon(path + '5.jpeg', path + '5_cbr.jpeg', kernel)
# print('cbr ok')