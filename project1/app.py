import Tkinter as tk
import tkMessageBox
import convolution
import filters
import operators
import cv2
import numpy as np
from PIL import Image, ImageTk

class App():
    def __init__(self, path):
        self.o_path = path
        self.d_path = path
        print(self.o_path)
        self.root = tk.Tk()
        self.root.title("Project 1")
        self.img = tk.PhotoImage(file = self.o_path)
        self.fm1 = tk.Frame(self.root)
        self.fm3 = tk.Frame(self.root)
        self.im_label = tk.Label(self.fm3, image=self.img)
        self.roberts = tk.Button(self.fm1, width=20, text="roberts", command = self.robertsCallBack)
        self.prewitt = tk.Button(self.fm1, width=20, text="prewitt", command = self.prewittCallBack)
        self.sobel = tk.Button(self.fm1, width=20, text="sobel", command = self.sobelCallBack)
        self.gaussian = tk.Button(self.fm1, width=20, text="gaussian", command = self.gaussianCallBack)
        self.mean = tk.Button(self.fm1, width=20, text="mean", command = self.meanCallBack)
        self.median = tk.Button(self.fm1, width=20, text="median", command = self.medianCallBack)

    def robertsCallBack(self):
        self.d_path = self.o_path[:-4] + "_roberts" + self.o_path[-4:]
        operators.roberts(self.o_path, self.d_path, False, False)
        self.img = tk.PhotoImage(file = self.d_path)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

    def prewittCallBack(self):
        self.d_path = self.o_path[:-4] + "_prewitt" + self.o_path[-4:]
        operators.prewitt(self.o_path, self.d_path, False, False)
        self.img = tk.PhotoImage(file = self.d_path)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

    def sobelCallBack(self):
        self.d_path = self.o_path[:-4] + "_sobel" + self.o_path[-4:]
        operators.sobel(self.o_path, self.d_path, False, False)
        self.img = tk.PhotoImage(file = self.d_path)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

    def gaussianCallBack(self):
        self.d_path = self.o_path[:-4] + "_gaussian" + self.o_path[-4:]
        filters.gaussian(self.o_path, self.d_path, 3, 0.5, False)
        self.img = tk.PhotoImage(file = self.d_path)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

    def meanCallBack(self):
        self.d_path = self.o_path[:-4] + "_mean" + self.o_path[-4:]
        filters.mean(self.o_path, self.d_path, 3, False)
        self.img = tk.PhotoImage(file = self.d_path)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

    def medianCallBack(self):
        self.d_path = self.o_path[:-4] + "_median" + self.o_path[-4:]
        filters.median(self.o_path, self.d_path, 3, False)
        self.img = tk.PhotoImage(file = self.d_path)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

    def display(self):
        self.roberts.pack(side=tk.LEFT)
        self.prewitt.pack(side=tk.LEFT)
        self.sobel.pack(side=tk.LEFT)
        self.gaussian.pack(side=tk.LEFT)
        self.mean.pack(side=tk.LEFT)
        self.median.pack(side=tk.LEFT)
        self.im_label.pack(side=tk.LEFT)
        self.fm1.pack(side=tk.TOP, fill=tk.BOTH, pady=10, expand=tk.YES)
        self.fm3.pack(side=tk.TOP, fill=tk.BOTH, expand=tk.YES)
        self.root.mainloop()