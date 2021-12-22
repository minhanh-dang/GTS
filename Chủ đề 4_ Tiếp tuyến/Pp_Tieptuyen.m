    %Phan nhap du lieu
    format long
    syms x real;%Khai b�o bien x l� kieu so thuc
    f = x^3+x+1;%Khai b�o h�m so f(x)
    a = -1;b =1;%Khai b�o khoang c�ch ly nghiem (a,b)
    epsi = 0.000001;%Khai b�o sai so cua xn
    c=cell(100);%Khai b�o mang chua c�c buoc t�nh cua xn
    %-------------------------------------------------------------
    if subs(f,x,a)==0 %Kiem tra gia tri dau mut a
        x=a
    else if subs(f,x,b)==0 %kiem tra gia tri dau mut b
            x=b 
        else
             %Tim min,max cua f'(x) tai [a,b]
            y=diff(f,x);%Dao h�m cua f(x)
            y1=diff(y,x);%Dao ham cua f'(x)
            %G�n min v� max cho hai dau mut
            miny=subs(y,x,a);
            maxy=subs(y,x,b);
            if miny*maxy>0 %Neu min*max>0 thi thuc hien chuong trinh
                x0=a;anpha=0.05; %Gan gia tri ban dau cho a
                if(miny>maxy)%Neu miny>maxy thi doi miny va maxy
                    tgian=miny;
                    miny=maxy;
                    maxy=tgian;
                end
                %Thuat to�n tim cuc tri cua f'(x)  
                dau=1;
                while (abs(subs(y1,x,x0))>0.00001)
                    if subs(y1,x,x0)<0
                        dau=-1;
                    end    
                    x0=x0+dau*anpha*subs(y1,x,x0);
                    if (x0>b) 
                        break
                    end    
                end
                if (x0>a) & (x0<b)
                   disp("Ham so co f''(x) doi dau tren (a,b)");
                else
                    if subs(f,x,a)*subs(f,x,b)<0
                        if subs(f,x,a)*subs(diff(diff(f,x)),x,a)>0 
                            x0=a; 
                        else x0=b;
                        end
                        n=1;
                        c{1}=double(x0);
                        disp([n double(x0)]);
                        delta=epsi*abs(miny); %T�nh f(xn) trong c�ng thuc sai so bac nhat
                        while abs(subs(f,x,x0))>= delta
                            x0=x0-subs(f,x,x0)/subs(y,x,x0);
                            n=n+1;
                            c{n}=double(x0);%Luu lai c�c buoc t�nh x0
                            disp([n double(x0)]);
                        end
                        x=double(x0)%Thong b�o ket qua
                    else disp("Khong co nghiem trong khoang [a,b]");
                end
            end    
        else disp("Ham so co f'(x) doi dau tren (a,b)")
        end
      end
    end