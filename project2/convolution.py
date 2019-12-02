import numpy as np
import cv2

def convolution_filter(img, c_filter):
    output = np.zeros(img.shape)
    low = c_filter.shape[0] // 2

    img_temp = np.pad(img, ((low, low),(low, low)), 'constant')
    (m, n) = img_temp.shape

    for i in range(low, m - low):
        for j in range(low, n - low):
            temp = (img_temp[i - low : i + low + 1, j - low : j + low + 1])
            output[i - low, j - low] = round(np.sum(c_filter * temp))
    return output

def convolution(in_path, out_path, c_filter, grey):
    if grey:
        img = cv2.imread(in_path, 0)
        output = convolution_filter(img, c_filter)
    else:
        img = cv2.imread(in_path, 1)
        b, g, r = cv2.split(img)
        new_b = convolution_filter(b, c_filter)
        new_g = convolution_filter(g, c_filter)
        new_r = convolution_filter(r, c_filter)
        output = cv2.merge([new_b, new_g, new_r])
    cv2.imwrite(out_path, output)
    return 0
