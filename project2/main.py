# Program to realize the convolution operation and
# the next filters:
#   Roberts operator;
#   Prewitt operator;
#   Sobel operator;
#   Gaussian filter, mean filter and Median filter
# Kernal size and sigma adjustable

import app

def main():
    a = app.App('image/2.jpeg')
    a.display()

if __name__=="__main__":
    main()
