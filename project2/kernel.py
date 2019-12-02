import tkinter as tk
import numpy as np
from common import *

class Kernel():
    def __init__(self, root, width, height, tips, TYPE):
        self.root = root
        self.width = width
        self.height = height
        self.show = False
        self.type = TYPE

        self.fm0 = tk.Frame(self.root)
        self.tip = tk.Label(self.fm0, text=tips)

        self.show = False

        self.valueSet = np.zeros((self.width, self.height))
        self.textSet = []
        self.fmSet = []
        for i in range(self.width):
            self.fmSet.append(tk.Frame(self.root))
            temp = []
            for j in range(self.height):
                temp.append(tk.Entry(self.fmSet[i], bd=3))
                temp[j].insert(0, '0')
            self.textSet.append(temp)

    def get_value(self):
        for i in range(self.width):
            for j in range(self.height):
                temp = self.textSet[i][j].get()
                if temp.isdigit():
                    self.valueSet[i, j] = int(temp)
                elif temp[0] == '-' and temp[1:].isdigit():
                    self.valueSet[i ,j] = int(temp[1:]) * -1
                else:
                    self.valueSet[i ,j] = float('inf')
        if self.type == TYPE.BINARY:
            if self.validationForBinary():
                return self.valueSet
            return []
        else:
            if self.validationForGray():
                return self.valueSet
            return []

    def validationForBinary(self):
        center = 0
        for i in range(self.width):
            for j in range(self.height):
                value = self.valueSet[i, j]
                if value != 0.0 and value != 1.0 and value != 2.0:
                    return False
                if value == 2.0:
                    center += 1
                    if center > 1:
                        return False
        if center != 1:
            return False
        return True

    def validationForGray(self):
        for i in range(self.width):
            for j in range(self.height):
                value = self.valueSet[i, j]
                if value == float('inf'):
                    return False
        return True

    def draw(self):
        self.fm0.pack(side=tk.TOP)
        self.tip.pack(side=tk.LEFT)
        for i in range(self.width):
            for j in range(self.height):
                self.textSet[i][j].pack(side=tk.LEFT)
            self.fmSet[i].pack(side=tk.TOP)

    def get_exist(self):
        return self.show
    
    def set_exist(self, show):
        self.show = show

    def forget(self):
        self.fm0.forget()
        for i in range(self.width):
            self.fmSet[i].forget()