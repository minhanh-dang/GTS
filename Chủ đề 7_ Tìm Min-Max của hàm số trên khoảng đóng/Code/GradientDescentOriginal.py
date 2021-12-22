# -*- coding: utf-8 -*-
"""
Created on Tue Mar 30 21:45:27 2021

@author: ADMIN
"""

from sympy import *
from sympy.parsing.sympy_parser import parse_expr
from matplotlib.animation import FuncAnimation
from sympy.plotting import plot
import matplotlib.pyplot as plt

#thuật toán Gradient Descent với ETA tĩnh, tìm 1 cực trị

#Khai báo các hằng số
ETA=0.01
EPS=1e-6
global expr
Input=int(input("1.Dùng hàm số cho trước.\n2.Tự nhập hàm số.\nLựa chọn của bạn:"))
if (Input==1):
     print("Lựa chọn hàm số cho trước:")
     print("1.f(x)=sin(x)+x-x^2")
     print("2.f(x)=x^4-4x^2+4")
     print("3.f(x)=e^x+sin(x^2)")
     print("4.f(x)=")
     print("5.f(x)=")
     ham=int(input("Chọn hàm số thứ:"))
     if (ham==1):
         expr="sin(x)+x-x**2"
     if (ham==2):
         expr="x**4-4*x**2+4"
     if(ham==3):
         expr="exp(x)+sin(x**2)"
    
if (Input==2):
    expr=input("Nhap ham so can tim\nf(x)=")
   
x= Symbol('x'),#sử dụng x làm biến toán học
f=lambdify(x, parse_expr(expr))#tạo hàm số f(x)
plot(parse_expr(expr),axis=True, ylim=(-10,10), autoscale = true)


def fp(x):#Tính đạo hàm
    dy= f(x+EPS)-f(x-EPS)
    dx= 2*EPS
    return dy/dx


def xetdau(x):
      if fp(x)==0: return 0
      if fp(x)>0: return +1
      if fp(x)<0: return -1
      
      
def GD1(eta,x0):#Thuật toán Gradient Descent
    sign=0
    sign=xetdau(x0)
    it=0
    varX=[x0]
    for it in range(3000000):
        x_new = x0 +sign* eta*fp(x0)
        if abs(fp(x_new)) < 1e-6:
            break        
        x0=x_new
        varX.append(x_new)
        #Vẽ đồ thi
    plt.xlabel("Số lần lặp")
    plt.ylabel("Giá trị của x")
    plt.plot(varX,ls='None',marker='.')
    return (x_new, it)
    
    # plot(diff(parse_expr(expr),x),(x, -10, 10),axis=True, ylim=(-10,10), autoscale = true)


#fp=lambdify(x,diff(parse_expr(expr),x))

#Khởi tạo các giá trị nhập vào


a=float(input("Nhập điểm xuất phát a="))

        

x_new=a
#chương trình chính

(minMax,itera)=GD1(ETA,x_new)

print("Số lần lặp khi đi tìm cực trị:",itera)
print("Điểm cực trị là ",minMax)