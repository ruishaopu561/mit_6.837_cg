import numpy as np
import cv2
import math

def mean_filter(img, filter_size):
    low = filter_size // 2
    img_temp = np.pad(img, ((low, low),(low, low)), 'constant')
    (m, n) = img_temp.shape
    output = np.zeros(img.shape)

    # size = 
    for i in range(low, m - low):
        for j in range(low, n - low):
            temp = (img_temp[i - low : i + low + 1, j - low : j + low + 1])
            output[i - low, j - low] = round(np.sum(temp) * 1.0 / (filter_size * filter_size))
    return output

def mean(in_path, out_path, filter_size, grey):
    if grey:
        img = cv2.imread(in_path, 0)
        output = mean_filter(img, filter_size)
    else:
        img = cv2.imread(in_path, 1)
        b, g, r = cv2.split(img)
        new_b = mean_filter(b, filter_size)
        new_g = mean_filter(g, filter_size)
        new_r = mean_filter(r, filter_size)
        output = cv2.merge([new_b, new_g, new_r])
    cv2.imwrite(out_path, output)

def median_filter(img, filter_size):
    low = filter_size // 2
    img_temp = np.pad(img, ((low, low),(low, low)), 'constant')
    (m, n) = img_temp.shape

    output = np.zeros(img.shape)

    for i in range(low, m - low):
        for j in range(low, n - low):
            temp = (img_temp[i - low : i + low + 1, j - low : j + low + 1])
            temp = temp.reshape(-1)
            output[i - low, j - low] = np.sort(temp)[filter_size * filter_size // 2]
    return output

def median(in_path, out_path, filter_size, grey):
    if grey:
        img = cv2.imread(in_path, 0)
        output = median_filter(img, filter_size)
    else:
        img = cv2.imread(in_path, 1)
        b, g, r = cv2.split(img)
        new_b = median_filter(b, filter_size)
        new_g = median_filter(g, filter_size)
        new_r = median_filter(r, filter_size)
        output = cv2.merge([new_b, new_g, new_r])
    cv2.imwrite(out_path, output)

def create_gauss_kernel(kernel_size, sigma):
    low = kernel_size // 2

    if sigma > 0:
        sigma = sigma
    else:
        sigma = 0.3 * ((kernel_size - 1) * 0.5 - 1) + 0.8

    kernel = np.zeros((kernel_size, kernel_size))
    for i in range(kernel_size):
        for j in range(kernel_size):
            x = j - low
            y = low - i
            kernel[i, j] = 1.0/(2*math.pi*sigma**2)*math.exp(-(x**2+y**2)/(2*sigma**2))
    kernel = kernel / np.sum(kernel)    
    return kernel

def gaussian_filter(img, kernel):
    (kernel_size, kernel_size) = kernel.shape
    low = kernel_size // 2

    img_temp = np.pad(img, ((low, low),(low, low)), 'constant')
    (m, n) = img_temp.shape

    output = np.zeros(img.shape)

    for i in range(low, m - low):
        for j in range(low, n - low):
            temp = (img_temp[i - low : i + low + 1, j - low : j + low + 1])
            output[i - low, j - low] = round(np.sum(kernel * temp))
    return output

def gaussian(in_path, out_path, filter_size, sigma, grey):
    kernel = create_gauss_kernel(filter_size, sigma)
    if grey:
        img = cv2.imread(in_path, 0)
        output = gaussian_filter(img, kernel)
    else:
        img = cv2.imread(in_path, 1)
        b, g, r = cv2.split(img)
        new_b = gaussian_filter(b, kernel)
        new_g = gaussian_filter(g, kernel)
        new_r = gaussian_filter(r, kernel)
        output = cv2.merge([new_b, new_g, new_r])
    cv2.imwrite(out_path, output)