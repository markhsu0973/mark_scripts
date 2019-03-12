#!/usr/bin/python
# -*- coding: UTF-8 -*-


# 步驟一：匯入 tkinter 模組。
from Tkinter import Tk, Label, Entry, Radiobutton, IntVar

# 步驟二：建立主視窗。
mainWin = Tk()
var = IntVar()
operation = [ '+', '-', '*', '/']

# 視窗標題
mainWin.title("gui example ")
# 視窗大小
mainWin.geometry("480x140")

# 步驟三：建立視窗控制項元件。
# 建立標籤
firstNumLabel = Label(mainWin, text="數字1")
secondNumLabel = Label(mainWin, text="數字2")
resultNumLabel = Label(mainWin, text="結果：")

# 按鈕 Click 事件處理函式
def cal():
    exp = firstNum.get() +operation[var.get()] + secondNum.get()
    result = "結果：" + str(eval(exp))
    resultNumLabel.config(text = result)

# 建立文字方塊
firstNum = Entry(mainWin, text="Num1")
secondNum = Entry(mainWin, text="Num2")

# 建立單選按鈕 aBtn ==> addition, sBtn ==> subtraction, mBtn ==> multiplication, dBtn ==> division
aBtn = Radiobutton(mainWin, text="+", variable=var, value=0, command=cal)
sBtn = Radiobutton(mainWin, text="-", variable=var, value=1, command=cal)
mBtn = Radiobutton(mainWin, text="*", variable=var, value=2, command=cal)
dBtn = Radiobutton(mainWin, text="/", variable=var, value=3, command=cal)

# 版面配置
firstNumLabel.grid(row=1,column=0)
secondNumLabel.grid(row=1,column=3)
resultNumLabel.grid(row=4,column=4)
firstNum.grid(row=1,column=1)
secondNum.grid(row=1,column=4)
aBtn.grid(row=0,column=2)
sBtn.grid(row=1,column=2)
mBtn.grid(row=2,column=2)
dBtn.grid(row=3,column=2)

# 步驟四： 進入事件處理迴圈。
mainWin.mainloop()
