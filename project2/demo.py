
'''4.控件焦点问题
创建三个Button，各自对应回调函数；将第二个Button设置焦点，程序运行是按“Enter”，判断
程序的打印结果
'''
from tkinter import *
 
 
def cb1():
    print('button1 clicked')
 
 
def printEventInfo(event):
    print('event.time = ', event.time)
    print('event.type = ', event.type)
    print('event.WidgetId = ', event.widget)
    print('event.KeySymbol = ', event.keysym)
 
 
def cb3():
    print('button3 clicked')
 
 
root = Tk()
 
b1 = Button(root, text='Button1', command=cb1)
b2 = Button(root, text='Button2')
b2.bind("<Enter>", printEventInfo)
b3 = Button(root, text='Button3', command=cb3)
b1.pack()
b2.pack()
b3.pack()
 
b2.focus_set()
root.mainloop()
