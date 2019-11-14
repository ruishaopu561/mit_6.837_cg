import numpy as np
import cv2
import math

def otsu(img):
    thre = 0
    (m, n) = img.shape
    pixCount= np.zeros(256)
    pixPro = np.zeros(256)
    deltaMax = 0 

    for i in range(m):
        for j in range(n):
            pixCount[int(img[i, j])] += 1
 
    for i in range(256):
        pixPro[i] = pixCount[i] * 1.0 / (m * n)
        # if i==0:
        #     print(pixPro[0])
 
    for i in range(1, 256):
        w0 = w1 = u0tmp = u1tmp = u0 = u1 = deltaTmp = 0  
        for j in range(1, 256):
            if j <= i:
                w0 += pixPro[j]
                u0tmp += j * pixPro[j] 
            else:
                w1 += pixPro[j]
                u1tmp += j * pixPro[j]

        if w0 == 0:
            u0 = (u0tmp + 1) / (w0 + 1.0)
        else:
            u0 = u0tmp / w0

        if w1 == 0:
            u1 = (u1tmp + 1) / (w1 + 1.0)
        else:
            u1 = u1tmp / w1

        deltaTmp = (float)(w0 * w1 * pow((u0 - u1), 2))
        
        if deltaTmp > deltaMax:
            deltaMax = deltaTmp
            thre = i  
    return thre

def roberts_convolution(img, thre):
    g_x = [-1, 0, 0, 1]
    g_y = [0, -1, 1, 0]

    img_temp = np.pad(img, ((0, 1),(0, 1)), 'constant')
    (m, n) = img_temp.shape

    output = np.zeros(img.shape)

    for i in range(0, m - 1):
        for j in range(0, n - 1):
            temp = (img_temp[i : i + 2, j : j + 2])
            temp = np.array(temp).reshape(-1)

            sum_x = np.sum(g_x * temp)
            sum_y = np.sum(g_y * temp)

            if thre:
                if sum_x + sum_y > 24:
                    output[i - 1, j - 1] = 255
                else:
                    output[i - 1, j - 1] = 0
            else:
                if sum_x + sum_y < 0:
                    output[i - 1, j - 1] = 0
                elif sum_x + sum_y > 255:
                    output[i - 1, j - 1] = 255
                else:
                    output[i - 1, j - 1] = sum_x + sum_y

    return output

def roberts(in_path, out_path, thre, grey):
    if grey:
        img = cv2.imread(in_path, 0)
        output = roberts_convolution(img, thre)
    else:
        img = cv2.imread(in_path, 1)
        b, g, r = cv2.split(img)
        new_b = roberts_convolution(b, thre)
        new_g = roberts_convolution(g, thre)
        new_r = roberts_convolution(r, thre)
        output = cv2.merge([new_b, new_g, new_r])
    cv2.imwrite(out_path, output)

def prewitt_convolution(img, thre):
    g_x = [1, 0, -1, 1, 0, -1, 1, 0, -1]
    g_y = [-1, -1, -1, 0, 0, 0, 1, 1, 1]

    img_temp = np.pad(img, ((1, 1),(1, 1)), 'constant')
    (m, n) = img_temp.shape

    output = np.zeros(img.shape)

    for i in range(1, m - 1):
        for j in range(1, n - 1):
            temp = (img_temp[i - 1 : i + 2, j - 1 : j + 2])
            temp = np.array(temp).reshape(-1)

            sum_x = np.sum(g_x * temp)
            sum_y = np.sum(g_y * temp)

            if thre:
                if sum_x + sum_y > 200:
                    output[i - 1, j - 1] = 255
                else:
                    output[i - 1, j - 1] = 0
            else:
                if sum_x + sum_y < 0:
                    output[i - 1, j - 1] = 0
                elif sum_x + sum_y > 255:
                    output[i - 1, j - 1] = 255
                else:
                    output[i - 1, j - 1] = sum_x + sum_y

    return output

def prewitt(in_path, out_path, thre, grey):
    if grey:
        img = cv2.imread(in_path, 0)
        output = prewitt_convolution(img, thre)
    else:
        img = cv2.imread(in_path, 1)
        b, g, r = cv2.split(img)
        new_b = prewitt_convolution(b, thre)
        new_g = prewitt_convolution(g, thre)
        new_r = prewitt_convolution(r, thre)
        output = cv2.merge([new_b, new_g, new_r])
    cv2.imwrite(out_path, output)

def sobel_convolution(img, thre):
    g_x = [-1, 0, 1, -2, 0, 2, -1, 0, 1]
    g_y = [1, 2, 1, 0, 0, 0, -1, -2, -1]

    img_temp = np.pad(img, ((1, 1),(1, 1)), 'constant')
    (m, n) = img_temp.shape

    output = np.zeros(img.shape)

    for i in range(1, m - 1):
        for j in range(1, n - 1):
            temp = (img_temp[i - 1 : i + 2, j - 1 : j + 2])
            temp = np.array(temp).reshape(-1)

            sum_x = np.sum(g_x * temp)
            sum_y = np.sum(g_y * temp)

            if thre:
                if sum_x + sum_y > 200:
                    output[i - 1, j - 1] = 255
                else:
                    output[i - 1, j - 1] = 0
            else:
                if sum_x + sum_y < 0:
                    output[i - 1, j - 1] = 0
                elif sum_x + sum_y > 255:
                    output[i - 1, j - 1] = 255
                else:
                    output[i - 1, j - 1] = sum_x + sum_y

    # thre = otsu(output)
    # print(thre)
    # for i in range(output.shape[0]):
    #     for j in range(output.shape[1]):
    #         if output[i, j] > 200:
    #             output[i, j] = 255
    #         else:
    #             output[i, j] = 0

    return output

def sobel(in_path, out_path, thre, grey):
    if grey:
        img = cv2.imread(in_path, 0)
        output = sobel_convolution(img, thre)
    else:
        img = cv2.imread(in_path, 1)
        b, g, r = cv2.split(img)
        new_b = sobel_convolution(b, thre)
        new_g = sobel_convolution(g, thre)
        new_r = sobel_convolution(r, thre)
        output = cv2.merge([new_b, new_g, new_r])
    cv2.imwrite(out_path, output)