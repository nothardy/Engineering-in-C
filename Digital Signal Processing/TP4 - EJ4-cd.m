%% DSP - EJERCICIO 4 C

clc; clear all;
close all;

n=[0:1:100];
xn=5*((0.8).^n);
xsuma=0;
figure(1);
stem(n,xn); title(' Grafico de la funcion x[n]');xlabel('Tiempo [n]');ylabel('x[n]');
for k=1:length(n)
    for m=1:16
        xsuma=xsuma+(xn(m)*exp(-i*2*pi*(1/16)*k*m));
    end
    xk(k)=xsuma;
    xsuma=0;
end
n2=linspace(0,2*pi,100);
figure(2);
subplot(2,1,1)
stem(n,abs(xk));title(' Grafico de la magnitud de la DFT estimada');xlabel('Frecuencia [W/k]');ylabel('X[W/k]');
subplot(2,1,2);
stem(n,angle(xk));title(' Grafico de la fase de la DFT estimada');xlabel('Frecuencia [W/k]');ylabel('X[W/f]');
n3=linspace(0,2*pi,16);
Xn=fft(xn,16);
figure(3);
subplot(2,1,1)
stem(n3,abs(Xn));title(' Grafico de la magnitud de la FFT');xlabel('Frecuencia [W/k]');ylabel('X[W/f]');
subplot(2,1,2)
stem(n3,angle(Xn));title(' Grafico de la fase de la FFT');xlabel('Frecuencia [W/k]');ylabel('X[W/f]');


%% DSP - EJERCICIO 4 D

clc; clear all;
close all;

n=[1:1:100];
for i=1:length(n)
    resto=rem(n(i),2);
    if resto==0
        xn(i)=-2;
    else
        xn(i)=3;
    end
end


xsuma=0;
figure(1);
stem(n,xn); title(' Grafico de la funcion x[n]');xlabel('Tiempo [n]');ylabel('x[n]');
for k=1:length(n)
    for m=1:16
        xsuma=xsuma+(xn(m)*exp(-i*2*pi*(1/16)*k*m));
    end
    xk(k)=xsuma;
    xsuma=0;
end
n2=linspace(0,2*pi,100);
figure(2);
subplot(2,1,1)
stem(n,abs(xk));title(' Grafico de la magnitud de la DFT estimada');xlabel('Frecuencia [W/k]');ylabel('X[W/k]');
subplot(2,1,2);
stem(n,angle(xk));title(' Grafico de la fase de la DFT estimada');xlabel('Frecuencia [W/k]');ylabel('X[W/f]');
n3=linspace(0,2*pi,16);
Xn=fft(xn,16);
figure(3);
subplot(2,1,1)
stem(n3,abs(Xn));title(' Grafico de la magnitud de la FFT');xlabel('Frecuencia [W/k]');ylabel('X[W/f]');
subplot(2,1,2)
stem(n3,angle(Xn));title(' Grafico de la fase de la FFT');xlabel('Frecuencia [W/k]');ylabel('X[W/f]');