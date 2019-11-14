import skimage
from skimage import io
import numpy as np
from PIL import Image

# noise_gs_img = util.random_noise(img,mode='gaussian')
# noise_salt_img = util.random_noise(img,mode='salt')
# noise_pepper_img = util.random_noise(img,mode='pepper')
# noise_sp_img = util.random_noise(img,mode='s&p')
# noise_speckle_img = util.random_noise(img,mode='speckle')

def addNoise(in_path, out_path, this_mode):
    img = Image.open(in_path)
    img = np.array(img)
    image = skimage.util.random_noise(img, mode=this_mode)
    io.imsave(out_path, image)
