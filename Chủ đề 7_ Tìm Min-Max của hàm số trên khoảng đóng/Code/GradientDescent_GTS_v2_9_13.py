#Một số kí hiệu toán học khi nhập hàm:
    #Dấu mũ (a^b): Nhập a**b
    #Lấy trị tuyệt đối(|f(x)|,f(|x|)):Nhập Abs(f(x)),f(Abs(x))
    #Lấy căn thức (sqrt()): Nhập sqrt()
    #Hàm logarith: log(f(x))/log(a) với a là cơ số
    #Hàm mũ: exp(f(x)*log(a)) với a là cơ số
##Chương trình chưa hỗ trợ hoàn toàn hàm số dạng f(x)=|g(x)|+d, nếu muốn tìm f(x) dạng này có cách 2 giải quyết:
    #Nhập thêm một hệ số offset=d sao cho k(x)=f(x)-offset và tìm cực trị của k(x), sau đó cộng thêm mỗi cực trị với offset
    #Giới hạn số lần lặp tối đa vừa đủ vì nếu gặp trường hợp trên, chương trình sẽ trả về kết quả sau khi số lần lặp đạt max, chọn giới hạn bé sẽ làm kq không đủ chính xác, quá lớn thì chương trình chạy lâu
from IPython.display import display, Math, Latex
from sympy import *
from sympy.parsing.sympy_parser import parse_expr
from matplotlib.animation import FuncAnimation
from sympy.plotting import plot
import matplotlib.pyplot as plt
import numpy as np
import time
import sys

#Khai báo các hằng số
ETA=0.0001
STEP=0.001 
global expr



def main():
    Input=int(input("1.Dùng hàm số cho trước.\n2.Tự nhập hàm số.\nLựa chọn của bạn:"))
    if (Input==1):
        print("Lựa chọn hàm số cho trước:")
        print("1.f(x)=sin(x)+x-x^2")
        print("2.f(x)=x^4-4x^2+4")
        print("3.f(x)=|e^x+sin(x^2)|")
        print("4.f(x)=cos(x^2)+sin(x^2)+x^2")
        print("5.f(x)=")
        ham=int(input("Chọn hàm số thứ:"))
        if (ham==1):
            expr="sin(x)+x-x**2"
        if (ham==2):
            expr="x**4-4*x**2+4"
        if(ham==3):
            expr="Abs(exp(x)+sin(x**2))"
        if(ham==4):
            expr="cos(x**2)+sin(x**2)+x**2"
    if (Input==2):
       expr=input("Nhap ham so can tim\nf(x)=")
   
    x= Symbol('x'),#sử dụng x làm biến toán học
    f=lambdify(x, parse_expr(expr))#tạo hàm số f(x)
    a=float(input("Nhập khoảng [a,b]\nNhập a="))
    b=float(input("Nhập b="))
    if abs(a)>abs(b):Xlim=abs(a)
    else:Xlim=abs(b)
    plot(parse_expr(expr),axis=True,xlim=(-Xlim,Xlim), ylim=(-2*Xlim,2*Xlim), autoscale = true,title="Đồ thị f(x)="+expr+"\n")
 

    def fp(x):#Tính đạo hàm
        dy= f(x+0.000001)-f(x-0.000001)
        dx= 2*0.000001
        return dy/dx
    def xetdau(x):
        if fp(x)==0: return 0
        if fp(x)>0: return +1
        if fp(x)<0: return -1
    def GD2(eta,x0):#Thuật toán gradient descent Eta động
        sign=0
        sign=xetdau(x0)
        it=0
        varX=[x0]
        for it in range(1000):
           deltaX=eta*fp(x0)*abs(f(x0)) # nhân thêm abs(f(x0)) khiến nó chạy chậm lại khi đến gần nghiệm của f(x)=0 (nếu hàm không có trị tuyệt đối thì sẽ làm GD chậm lại)
           if deltaX>0.1 : deltaX=0.1   #giới hạn tốc độ dịch chuyển của x(phòng trường hợp x nhảy quá xa)
           if deltaX<-0.1: deltaX=-0.1
           x_new = x0 + sign*deltaX 
           if abs(fp(x_new))<0.005:abslim=1e-15
           else: abslim=1e-7
           if abs(fp(x_new)) < 1e-20 or abs(f(x_new))<abslim or x_new>b:
               break
           
           #eta động
           if (fp(x_new)*fp(x0)>0 ):eta*=3
           if fp(x_new)*fp(x0)<0:eta/=5
           x0=x_new
           varX.append(x_new)
        if x_new<=b:
        
            plt.xlabel("Số lần lặp")
            plt.ylabel("Giá trị của x")
            plt.plot(varX,ls='None',marker='.')
        
        return (x_new, it, sign)
    


#fp=lambdify(x,diff(parse_expr(expr),x))


#cài đặt giá trị max, min ban đầu
    if(f(a)>f(b)):
       tmax=a; tmin=b
    else: 
       tmin=a; tmax=b

    Sum=0 #tổng số lần lặp
    x_new=a
    localMin=[]#        Tạo 1 list để lưu cực tiểu
    localMax=[]#        Tạop 1 list để lưu cực đại
    iterationOfEachMinMax=[] #Tạo 1 list để đếm mỗi lần lặp
    i=0
 
#chương trình chính

    while(i<300):
       (minMax,itera,sign)=GD2(ETA,x_new)
       x_new=minMax
    # Kiểm tra điểm tới hạn có phải cực trị hay không?
       if fp(x_new-0.1)*fp(x_new+0.1)<0 :
         
         if( sign>0  and minMax <= b ):
            localMax.append(minMax)
            if f(minMax)>f(tmax): tmax=minMax
         if(sign<0   and minMax <= b):
            localMin.append(minMax) 
            if f(minMax)<f(tmin): tmin=minMax
         iterationOfEachMinMax.append(itera)
         Sum+=itera
       while (abs(fp(x_new))<1e-9 or abs(f(x_new))<1e-3  and x_new<b):
         x_new+= STEP
       i+=1
       if(x_new>b): break
    plt.show()
    
    print("Số lần lặp khi đi tìm mỗi cực trị:",iterationOfEachMinMax)
    print("\nTổng số lần lặp:",Sum)
    print("\nLocal min",localMin)
    print("\nLocal max",localMax)
    print("\nGlobal min (",tmin,",",f(tmin),")" )
    print("\nGlobal max (",tmax,",",f(tmax),")")

main()
luachon=str(input("Bạn có muốn chạy lại chường trình không? Yes/No\nLựa chọn của bạn:"))
Luachon=luachon.upper()
while (Luachon=='YES' or Luachon=='Y'):
    main()
    luachon=str(input("Bạn có muốn chạy lại chường trình không? Yes/No\nLựa chọn của bạn:"))
    Luachon=luachon.upper()
if (Luachon=='NO' or Luachon=='N'):
    text="Chương trình đang kết thúc . . .\n"
    for char in text:
        sys.stdout.write (char)
        time.sleep(0.07)
    
    print("Đã kết thúc!")