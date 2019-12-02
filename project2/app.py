import tkinter as tk
import tkinter.filedialog
import cv2
import numpy as np
from PIL import Image, ImageTk

import convolution
import filters
import operators
import common
import kernel as k
import binary
import grayvalue as gray

class App():
    def __init__(self, path):
        self.origin_path = path
        self.gray_path = path
        self.binary_path = path
        self.noise_path = path
        self.draw_path = path
        self.mask_path = path

        self.root = tk.Tk()
        self.root.title("Project 2")

        self.menubar = tk.Menu(self.root)

        self.commonmenu = tk.Menu(self.menubar, tearoff=0)
        self.commonmenu.add_command(label="open", command=self.openCallback)
        self.commonmenu.add_command(label="add noise", command=self.addNoiseCallback)
        self.commonmenu.add_command(label="withdraw", command=self.withdrawCallback)
        self.menubar.add_cascade(label="File", menu=self.commonmenu)

        self.filtermenu = tk.Menu(self.menubar, tearoff=0)
        self.filtermenu.add_command(label="convolution", command=self.convolutionCallback)
        self.filtermenu.add_command(label="gaussian", command=self.gaussianCallback)
        self.filtermenu.add_command(label="median", command=self.medianCallback)
        self.filtermenu.add_command(label="mean", command=self.meanCallback)
        self.menubar.add_cascade(label="Filter", menu=self.filtermenu)

        self.operatormenu = tk.Menu(self.menubar, tearoff=0)
        self.operatormenu.add_command(label="roberts", command=self.robertsCallback)
        self.operatormenu.add_command(label="prewitt", command=self.prewittCallback)
        self.operatormenu.add_command(label="sobel", command=self.sobelCallback)
        self.menubar.add_cascade(label="Operater", menu=self.operatormenu)

        self.morphmenu = tk.Menu(self.menubar, tearoff=0)
        self.morphmenu.add_command(label="generate gray", command=self.generateGrayCallback)
        self.morphmenu.add_command(label="generate binary", command=self.generateBinaryCallback)
        self.morphmenu.add_command(label="Set Mask", command=self.setMaskCallback)
        self.morphmenu.add_command(label="Conditional Dilation", command=self.conditionDilationCallback)
        self.morphmenu.add_separator()

        self.edgemenu = tk.Menu(self.morphmenu)
        self.edgemenu.add_command(label='Standard', command=self.edgeStandardCallback)
        self.edgemenu.add_command(label='Internal', command=self.edgeInternalCallback)
        self.edgemenu.add_command(label='External', command=self.edgeExternalCallback)
        self.morphmenu.add_cascade(label="Edge Detection", menu=self.edgemenu, underline=0)

        self.gradientmenu = tk.Menu(self.morphmenu)
        self.gradientmenu.add_command(label='Standard', command=self.gradientStandardCallback)
        self.gradientmenu.add_command(label='Internal', command=self.gradientInternalCallback)
        self.gradientmenu.add_command(label='External', command=self.gradientExternalCallback)
        self.morphmenu.add_cascade(label="Gradient", menu=self.gradientmenu, underline=0)

        self.reconmenu = tk.Menu(self.morphmenu)
        self.reconmenu.add_command(label='Reconstruction Opening', command=self.reconOpeningCallback)
        self.reconmenu.add_command(label='Reconstruction Closing', command=self.reconClosingCallback)
        self.reconmenu.add_command(label='Geodesic Opening', command=self.geodesicOpeningCallback)
        self.reconmenu.add_command(label='Geodesic Closing', command=self.geodesicClosingCallback)
        self.morphmenu.add_cascade(label="Gray Value Reconstruction", menu=self.reconmenu, underline=0)

        self.menubar.add_cascade(label="Morphological", menu=self.morphmenu)

        self.filter_fm = tk.Frame(self.root)
        self.kernel_label = tk.Label(self.filter_fm, text=" filter size: ")
        self.kernel_text = tk.Entry(self.filter_fm, bd=3)
        
        self.sigema_label = tk.Label(self.filter_fm, text=" sigema: ")
        self.sigema_text = tk.Entry(self.filter_fm, bd=3)

        self.se_fm = tk.Frame(self.root)
        self.se_width_label = tk.Label(self.se_fm, text=" SE width: ")
        self.se_width_text = tk.Entry(self.se_fm, bd=3)
        self.se_height_label = tk.Label(self.se_fm, text=" SE heigth: ")
        self.se_height_text = tk.Entry(self.se_fm, bd=3)
        self.se_binary = tk.Button(self.se_fm, text="binary kernel", command=self.clickBinaryCallback)
        self.se_gray = tk.Button(self.se_fm, text="gray kernel", command=self.clickGrayCallback)

        self.image_fm = tk.Frame(self.root)
        image = Image.open(self.origin_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label = tk.Label(self.image_fm, image=self.img) 

        self.kernel = k.Kernel(self.root, 3, 3, "tips", common.TYPE.BINARY)

    def setMaskCallback(self):
        self.mask_path = tkinter.filedialog.askopenfilename(filetypes=[("JPG",".jpg"),("PNG",".png"),("JPEG",".jpeg")])
        image = Image.open(self.mask_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

    def generateGrayCallback(self):
        path = self.origin_path.split('.')
        temp = cv2.imread(self.origin_path, 0)
        self.gray_path = path[0] + "_gray." + path[1]
        cv2.imwrite(self.gray_path, temp)

    def generateBinaryCallback(self):
        path = self.origin_path.split('.')

        img = cv2.imread(self.origin_path)
        grayImage = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        ret, temp = cv2.threshold(grayImage, 127, 255, cv2.THRESH_BINARY)

        self.binary_path = path[0] + "_binary." + path[1]
        cv2.imwrite(self.binary_path, temp)

    def clickBinaryCallback(self):
        if self.getSEWidth() == -1:
            return
        if self.getSEHeight() == -1:
            return
        if self.kernel.get_exist():
            self.kernel.forget()
        self.kernel = k.Kernel(self.root, self.getSEWidth(), self.getSEHeight(), "tips! ", common.TYPE.BINARY)
        self.image_fm.forget()
        self.kernel.draw()
        self.kernel.set_exist(True)

    def clickGrayCallback(self):
        if self.getSEWidth() == -1:
            return
        if self.getSEHeight() == -1:
            return
        if self.kernel.get_exist():
            self.kernel.forget()
        self.kernel = k.Kernel(self.root, self.getSEWidth(), self.getSEHeight(), "tips! ", common.TYPE.GARY)
        self.image_fm.forget()
        self.kernel.draw()
        self.kernel.set_exist(True)

    def conditionDilationCallback(self):
        values = self.kernel.get_value()
        if values == []:
            return
        path = self.binary_path.split('.')
        self.draw_path = path[0] + "_dilation." + path[1]
        binary.conditional_dilation(self.binary_path, self.mask_path, self.draw_path, np.array(values))
        
        image = Image.open(self.draw_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

        self.kernel.set_exist(False)
        self.kernel.forget()
        self.image_fm.pack(side=tk.TOP, fill=tk.BOTH, expand=tk.YES)

    def edgeStandardCallback(self):
        values = self.kernel.get_value()
        if values == []:
            return
        path = self.binary_path.split('.')
        self.draw_path = path[0] + "_edge_standard." + path[1]
        binary.edge_standard(self.binary_path, self.draw_path, np.array(values))
        
        image = Image.open(self.draw_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

        self.kernel.set_exist(False)
        self.kernel.forget()
        self.image_fm.pack(side=tk.TOP, fill=tk.BOTH, expand=tk.YES)

        return 0

    def edgeInternalCallback(self):
        values = self.kernel.get_value()
        if values == []:
            return
        path = self.binary_path.split('.')
        self.draw_path = path[0] + "_edge_internal." + path[1]
        binary.edge_internal(self.binary_path, self.draw_path, np.array(values))
        
        image = Image.open(self.draw_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

        self.kernel.set_exist(False)
        self.kernel.forget()
        self.image_fm.pack(side=tk.TOP, fill=tk.BOTH, expand=tk.YES)

        return 0

    def edgeExternalCallback(self):
        values = self.kernel.get_value()
        if values == []:
            return
        path = self.binary_path.split('.')
        self.draw_path = path[0] + "_edge_external." + path[1]
        binary.edge_external(self.binary_path, self.draw_path, np.array(values))
        
        image = Image.open(self.draw_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

        self.kernel.set_exist(False)
        self.kernel.forget()
        self.image_fm.pack(side=tk.TOP, fill=tk.BOTH, expand=tk.YES)

        return 0

    def gradientStandardCallback(self):
        values = self.kernel.get_value()
        if values == []:
            return
        path = self.gray_path.split('.')
        self.draw_path = path[0] + "_gradient_standard." + path[1]
        gray.gradient_standard(self.gray_path, self.draw_path, np.array(values))

        image = Image.open(self.draw_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

        self.kernel.set_exist(False)
        self.kernel.forget()
        self.image_fm.pack(side=tk.TOP, fill=tk.BOTH, expand=tk.YES)

        return 0

    def gradientInternalCallback(self):
        values = self.kernel.get_value()
        if values == []:
            return
        path = self.gray_path.split('.')
        self.draw_path = path[0] + "_gradient_internal." + path[1]
        gray.gradient_internal(self.gray_path, self.draw_path, np.array(values))

        image = Image.open(self.draw_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

        self.kernel.set_exist(False)
        self.kernel.forget()
        self.image_fm.pack(side=tk.TOP, fill=tk.BOTH, expand=tk.YES)

        return 0

    def gradientExternalCallback(self):
        values = self.kernel.get_value()
        if values == []:
            return
        path = self.gray_path.split('.')
        self.draw_path = path[0] + "_gradient_external." + path[1]
        gray.gradient_external(self.gray_path, self.draw_path, np.array(values))

        image = Image.open(self.draw_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

        self.kernel.set_exist(False)
        self.kernel.forget()
        self.image_fm.pack(side=tk.TOP, fill=tk.BOTH, expand=tk.YES)

        return 0

    def reconOpeningCallback(self):
        values = self.kernel.get_value()
        if values == []:
            return
        path = self.gray_path.split('.')
        self.draw_path = path[0] + "_recon_open." + path[1]
        gray.obr_recon(self.gray_path, self.draw_path, np.array(values))

        image = Image.open(self.draw_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

        self.kernel.set_exist(False)
        self.kernel.forget()
        self.image_fm.pack(side=tk.TOP, fill=tk.BOTH, expand=tk.YES)

        return 0

    def reconClosingCallback(self):
        values = self.kernel.get_value()
        if values == []:
            return
        path = self.gray_path.split('.')
        self.draw_path = path[0] + "_recon_close." + path[1]
        gray.cbr_recon(self.gray_path, self.draw_path, np.array(values))

        image = Image.open(self.draw_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

        self.kernel.set_exist(False)
        self.kernel.forget()
        self.image_fm.pack(side=tk.TOP, fill=tk.BOTH, expand=tk.YES)

        return 0

    def geodesicOpeningCallback(self):
        values = self.kernel.get_value()
        if values == []:
            return
        path = self.gray_path.split('.')
        self.draw_path = path[0] + "_geodesic_open." + path[1]
        gray.geodesic_open(self.gray_path, self.mask_path, self.draw_path, np.array(values))

        image = Image.open(self.draw_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

        self.kernel.set_exist(False)
        self.kernel.forget()
        self.image_fm.pack(side=tk.TOP, fill=tk.BOTH, expand=tk.YES)

        return 0

    def geodesicClosingCallback(self):
        values = self.kernel.get_value()
        if values == []:
            return
        path = self.gray_path.split('.')
        self.draw_path = path[0] + "_geodesic_close." + path[1]
        gray.geodesic_close(self.gray_path, self.mask_path, self.draw_path, np.array(values))

        image = Image.open(self.draw_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

        self.kernel.set_exist(False)
        self.kernel.forget()
        self.image_fm.pack(side=tk.TOP, fill=tk.BOTH, expand=tk.YES)

        return 0

    def convolutionCallback(self):
        kernel = [-1, -1, -1, -1, 9, -1, -1, -1, -1]
        kernel = np.array(kernel)
        path = self.origin_path.split('.')
        self.draw_path = path[0] + "_convolution." + path[1]
        convolution.convolution(self.origin_path, self.draw_path, kernel, False)
        image = Image.open(self.draw_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

    def robertsCallback(self):
        path = self.origin_path.split('.')
        self.draw_path = path[0] + "_roberts." + path[1]
        operators.roberts(self.origin_path, self.draw_path, False, False)
        image = Image.open(self.draw_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

    def prewittCallback(self):
        path = self.origin_path.split('.')
        self.draw_path = path[0] + "_prewitt." + path[1]
        operators.prewitt(self.origin_path, self.draw_path, False, False)
        image = Image.open(self.draw_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

    def sobelCallback(self):
        path = self.origin_path.split('.')
        self.draw_path = path[0] + "_sobel." + path[1]
        operators.sobel(self.origin_path, self.draw_path, False, False)
        image = Image.open(self.draw_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

    def gaussianCallback(self):
        kernel = self.getKernelSize()
        sigema = self.getSigema()
        if kernel==0 or sigema==-1:
            return

        path = self.noise_path.split('.')
        self.draw_path = path[0] + "_gaussian." + path[1]
        filters.gaussian(self.noise_path, self.draw_path, kernel, sigema, False)
        image = Image.open(self.draw_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

    def meanCallback(self):
        kernel = self.getKernelSize()
        if kernel==0:
            return

        path = self.noise_path.split('.')
        self.draw_path = path[0] + "_mean." + path[1]
        filters.mean(self.noise_path, self.draw_path, kernel, False)
        image = Image.open(self.draw_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

    def medianCallback(self):
        kernel = self.getKernelSize()
        if kernel==0:
            return

        path = self.noise_path.split('.')
        self.draw_path = path[0] + "_median." + path[1]
        filters.median(self.noise_path, self.draw_path, kernel, False)
        image = Image.open(self.draw_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

    def openCallback(self):
        self.origin_path = tkinter.filedialog.askopenfilename(filetypes=[("JPG",".jpg"),("PNG",".png"),("JPEG",".jpeg")])
        image = Image.open(self.origin_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

    def addNoiseCallback(self):
        path = self.origin_path.split('.')
        self.noise_path = path[0] + "_noise." + path[1]
        common.addNoise(self.origin_path, self.noise_path, 's&p')
        image = Image.open(self.noise_path)
        self.img = ImageTk.PhotoImage(image)
        self.im_label.configure(image=self.img)
        self.im_label.pack()

    def withdrawCallback(self):
        image = Image.open(self.origin_path)
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

    def getSEWidth(self):
        text = self.se_width_text.get()
        if text.isdigit():
            if int(text) < 2:
                self.se_width_text.delete(0, tk.END)
                self.se_width_text.insert(0, 'Input SE width in 2~n.')
                return -1
            return int(text)
        else:
            self.se_width_text.delete(0, tk.END)
            self.se_width_text.insert(0, 'Input SE width in 2~n.')
            return -1

    def getSEHeight(self):
        text = self.se_height_text.get()
        if text.isdigit():
            if int(text) < 2:
                self.se_height_text.delete(0, tk.END)
                self.se_height_text.insert(0, 'Input SE heigth in 2~n.')
                return -1
            return int(text)
        else:
            self.se_height_text.delete(0, tk.END)
            self.se_height_text.insert(0, 'Input SE heigth in 2~n.')
            return -1

    def display(self):
        self.root.config(menu=self.menubar)

        self.kernel_label.pack(side=tk.LEFT)
        self.kernel_text.pack(side=tk.LEFT)
        self.sigema_label.pack(side=tk.LEFT)
        self.sigema_text.pack(side=tk.LEFT)
        self.filter_fm.pack(side=tk.TOP, fill=tk.BOTH, pady=5, expand=tk.YES)

        self.se_width_label.pack(side=tk.LEFT)
        self.se_width_text.pack(side=tk.LEFT)
        self.se_height_label.pack(side=tk.LEFT)
        self.se_height_text.pack(side=tk.LEFT)
        self.se_binary.pack(side=tk.LEFT, padx=5)
        self.se_gray.pack(side=tk.LEFT, padx=5)
        self.se_fm.pack(side=tk.TOP, fill=tk.BOTH, pady=5, expand=tk.YES)

        self.im_label.pack(side=tk.LEFT)
        self.image_fm.pack(side=tk.TOP, fill=tk.BOTH, expand=tk.YES)

        self.root.mainloop()