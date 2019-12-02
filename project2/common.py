import skimage
from skimage import io
import numpy as np
from PIL import Image
from enum import Enum

class TYPE(Enum):
    BINARY = 1
    GARY = 2
    STANDARD = 3
    INTERNAL = 4
    EXTERNAL = 5

def addNoise(in_path, out_path, this_mode):
    img = Image.open(in_path)
    img = np.array(img)
    image = skimage.util.random_noise(img, mode=this_mode)
    io.imsave(out_path, image)

def ifEqual(image, output):
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            if image[i, j] != output[i, j]:
                return False
    return True
