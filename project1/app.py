import tkinter as tk
import tkinter.filedialog
import cv2
import numpy as np
from PIL import Image, ImageTk

import convolution
import filters
import operators
import common

class App():
    def __init__(self, path):
        self.o_path = path
        self.n_path = path
        self.d_path = path
        print(self.o_path, self.n_path, self.d_path)
        self.root = tk.Tk()
        self.root.title("Project 1")

        self.menubar = tk.Menu(self.root)

        self.commonmenu = tk.Menu(self.menubar, tearoff=0)
        self.commonmenu.add_command(label="open", command=self.openCallBack)
        self.commonmenu.add_command(label="add noise", command=self.addNoiseCallBack)
        self.commonmenu.add_command(label="withdraw", command=self.withdrawCallBack)
        self.menubar.add_cascade(label="File", menu=self.commonmenu)

        self.filtermenu = tk.Menu(self.menubar, tearoff=0)
        self.filtermenu.add_command(label="convolution", command=self.convolutionCallBack)
        self.filtermenu.add_command(label="gaussian", command=self.gaussianCallBack)
        self.filtermenu.add_command(label="median", command=self.medianCallBack)
        self.filtermenu.add_command(label="mean", command=self.meanCallBack)
        self.menubar.add_cascade(label="Filter", menu=self.filtermenu)

        self.operatormenu = tk.Menu(self.menubar, tearoff=0)
        self.operatormenu.add_command(label="roberts", command=self.robertsCallBack)
        self.operatormenu.add_command(label="prewitt", command=self.prewittCallBack)
        self.operatormenu.add_command(label="sobel", command=self.sobelCallBack)
        self.menubar.add_cascade(label="Operater", menu=self.operatormenu)

        self.fm1 = tk.Frame(self.root)
        self.kernel_label = tk.Label(self.fm1, text=" filter size: ")
        self.kernel_text = tk.Entry(self.fm1, bd=3)
        
        self.sigema_label = tk.Label(self.fm1, text=" sigema: ")
        self.sigema_text = tk.Entry(self.fm1, bd=3)

        self.fm2 = tk.Frame(self.root)
        image = Image.open(self.o_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label = tk.Label(self.fm2, image=self.img) 

    def convolutionCallBack(self):
        kernel = [-1, -1, -1, -1, 9, -1, -1, -1, -1]
        kernel = np.array(kernel)
        path = self.o_path.split('.')
        self.d_path = path[0] + "_convolution." + path[1]
        convolution.convolution(self.o_path, self.d_path, kernel, False)
        image = Image.open(self.d_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

    def robertsCallBack(self):
        path = self.o_path.split('.')
        self.d_path = path[0] + "_roberts." + path[1]
        operators.roberts(self.o_path, self.d_path, False, False)
        image = Image.open(self.d_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

    def prewittCallBack(self):
        path = self.o_path.split('.')
        self.d_path = path[0] + "_prewitt." + path[1]
        operators.prewitt(self.o_path, self.d_path, False, False)
        image = Image.open(self.d_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

    def sobelCallBack(self):
        path = self.o_path.split('.')
        self.d_path = path[0] + "_sobel." + path[1]
        operators.sobel(self.o_path, self.d_path, False, False)
        image = Image.open(self.d_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

    def gaussianCallBack(self):
        kernel = self.getKernelSize()
        sigema = self.getSigema()
        if kernel==0 or sigema==-1:
            return

        path = self.n_path.split('.')
        self.d_path = path[0] + "_gaussian." + path[1]
        filters.gaussian(self.n_path, self.d_path, kernel, sigema, False)
        print(kernel, sigema, self.n_path, self.d_path)
        image = Image.open(self.d_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

    def meanCallBack(self):
        kernel = self.getKernelSize()
        print(kernel)
        if kernel==0:
            return

        path = self.n_path.split('.')
        self.d_path = path[0] + "_mean." + path[1]
        filters.mean(self.n_path, self.d_path, kernel, False)
        image = Image.open(self.d_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

    def medianCallBack(self):
        kernel = self.getKernelSize()
        print(kernel)
        if kernel==0:
            return

        path = self.n_path.split('.')
        self.d_path = path[0] + "_median." + path[1]
        filters.median(self.n_path, self.d_path, kernel, False)
        image = Image.open(self.d_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

    def openCallBack(self):
        self.o_path = tkinter.filedialog.askopenfilename(filetypes=[("JPG",".jpg"),("PNG",".png"),("JPEG",".jpeg")])
        image = Image.open(self.o_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

    def addNoiseCallBack(self):
        path = self.o_path.split('.')
        self.n_path = path[0] + "_noise." + path[1]
        common.addNoise(self.o_path, self.n_path, 's&p')
        image = Image.open(self.n_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

    def withdrawCallBack(self):
        print(self.o_path)
        image = Image.open(self.o_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

    def getKernelSize(self):
        text = self.kernel_text.get()
        if text=='1':
            return 3
        elif text=='2':
            return 5
        elif text=='3':
            return 7
        elif text=='4':
            return 9
        elif text=='5':
            return 11
        else:
            self.kernel_text.delete(0, tk.END)
            self.kernel_text.insert(0, 'Input kernel size in 1~5.')
            return 0

    def getSigema(self):
        text = self.sigema_text.get()
        try:
            sigema = float(text)
            if sigema >= 1 or sigema <= 0:
                self.sigema_text.delete(0, tk.END)
                self.sigema_text.insert(0, 'Input sigema in 0~1.')
                return -1
            else:
                return sigema
        except ValueError:
            self.sigema_text.delete(0, tk.END)
            self.sigema_text.insert(0, 'Input sigema in 0~1.')
            return -1

    def display(self):
        self.root.config(menu=self.menubar)

        self.kernel_label.pack(side=tk.LEFT)
        self.kernel_text.pack(side=tk.LEFT)
        self.sigema_label.pack(side=tk.LEFT)
        self.sigema_text.pack(side=tk.LEFT)
        self.fm1.pack(side=tk.TOP, fill=tk.BOTH, pady=5, expand=tk.YES)

        self.im_label.pack(side=tk.LEFT)
        self.fm2.pack(side=tk.TOP, fill=tk.BOTH, expand=tk.YES)
        self.root.mainloop()