# -*- coding: utf-8 -*-
import cv2
import numpy as np
import utils

def strokeEdges(src, dst, blurKsize = 7, edgeKsize = 5):
    if blurKsize >= 3:
        blurredSrc = cv2.medianBlur(src, blurKsize)
        graySrc = cv2.cvtColor(blurredSrc, cv2.COLOR_BGR2GRAY)
    else:
        graySrc = cv2.cvtColor(src, cv2.COlOR_BGR2GRAY)
    cv2.Laplacian(graySrc, cv2.CV_8U, graySrc, ksize = edgeKsize)
    normalizedInverseAlpha = (1.0 / 255) * (255 - graySrc)
    channels = cv2.split(src)
    for channel in channels:
        channel[:] = channel * normalizedInverseAlpha
    cv2.merge(channels, dst)

# def main():
#     img = cv2.imread("../assets/2.jpeg", 1)
#     strokeEdges(img, img)
#     cv2.imshow("img", img)
#     cv2.waitKey(0)
#     cv2.destroyAllWindows()

# main()

class VConvolutionFilter(object):
    """A filter that applies a convolution to V (or all of BGR)."""
    def __init__(self, kernel):
        self._kernel = kernel
    
    def apply(self, src, dst):
        """Apply the filter with a BGR or gray source/dstination."""
        cv2.filter2D(src, -1, self._kernel, dst)

# 锐化滤波器，存在负值，中央与周围差距变大
class SharpenFilter(VConvolutionFilter):
    """A sharpen filter with a 1-pixel radius."""
    
    def __init__(self):
        kernel = np.array([[-1,-1,-1],
                           [-1, 9,-1],
                           [-1,-1,-1]])
        VConvolutionFilter.__init__(self, kernel)

# 权重和为0，边缘检测核
class FindEdgesFilter(VConvolutionFilter):
    """An edge-finding filter with a 1-pixel radius."""
    
    def __init__(self):
        kernel = np.array([[-1,-1,-1],
                           [-1, 8,-1],
                           [-1,-1,-1]])
        VConvolutionFilter.__init__(self, kernel)

# 模糊滤波器，权重和通常为1，且临近像素的权重全为正        
class BlurFilter(VConvolutionFilter):
    """A blur filter with a 2-pixel radius."""

    def __init__(self):
        kernel = np.array([[0.04,0.04,0.04,0.04,0.04],
                           [0.04,0.04,0.04,0.04,0.04],
                           [0.04,0.04,0.04,0.04,0.04],
                           [0.04,0.04,0.04,0.04,0.04],
                           [0.04,0.04,0.04,0.04,0.04]])
        VConvolutionFilter.__init__(self, kernel)
        
# 不对称的核，有锐化和模糊的双重作用
class EmbossFilter(VConvolutionFilter):
    """An emboss filter with a 1-pixel radius."""
    
    def __init__(self):
        kernel = np.array([[-2,-1, 0],
                           [-1, 1, 1],
                           [ 0, 1, 2]])
        VConvolutionFilter.__init__(self, kernel)