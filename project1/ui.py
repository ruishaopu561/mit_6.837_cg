# Program to realize the convolution operation and
# the next filters:
#   Roberts operator;
#   Prewitt operator;
#   Sobel operator;
#   Gaussian filter, mean filter and Median filter
# Kernal size and sigma adjustable

import app

def main():
    path = "./3.png"
    a = app.App(path)
    a.display()

if __name__=="__main__":
    main()