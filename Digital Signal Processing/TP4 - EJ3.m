%% DSP - EJERCICIO 3
clc;
clear all;
xk=zeros(1,8);
xsuma=0;
xn=[1,1,1,1,0,0,0,0];
for k=1:8
    for n=1:8
        xsuma=xsuma+((xn(n))*exp((-i*(2*pi*n*k))./8));
    end
    xk(k)=xsuma;
    xsuma=0;
end
n=[0:1:7];
subplot(2,1,1)
stem(n,abs(xk));
    
Xn=fft(xn);
subplot(2,1,2)
stem(n,abs(Xn));