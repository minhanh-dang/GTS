# -*- coding: utf-8 -*-
"""
Created on Tue Mar 30 22:01:58 2021

@author: ADMIN
"""

from sympy import *
from sympy.parsing.sympy_parser import parse_expr
from matplotlib.animation import FuncAnimation
from sympy.plotting import plot
import matplotlib.pyplot as plt
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
   

def duyet(a,b):
    #cài đặt giá trị
    if(f(a)>f(b)):
        tmax=a; tmin=b
    else: 
        tmin=a; tmax=b
    it=0
    step=(b-a)/2**15
    x=a
    while x<=b:
        if f(x)<f(tmin):tmin=x
        if f(x)>f(tmax):tmax=x
        x+=step
        it+=1
    return (tmin,tmax,it)
#plot(parse_expr(expr),axis=True, ylim=(-10,10), autoscale = true)
   
   
x= Symbol('x')#sử dụng x làm biến toán học
f=lambdify(x, parse_expr(expr))#tạo hàm số f(x)
a=float(input("Nhập khoảng [a,b]\nNhập a="))
b=float(input("Nhập b="))
        

    

(gmin,gmax,itera)=duyet(a,b)
print("Global min (",gmin,",",f(gmin),")" )
print("Global max (",gmax,",",f(gmax),")")
print("Tổng số lần lặp:",itera)