%% DSP - EJERCICIO 2

clc; clear all;

F=100;
Fs=1000;
T=1/F;
Ts=1/Fs;
limt=100/F;

t=[-10*T:0.00001:10*T];
xc=sin(2*pi*F*t);
subplot(2,1,1);
plot(t,xc)

%   Obtengo la señal muestreada xn.
n=[-limt*F:1:limt*F];
xn=sin(F*2*pi*n*Ts);
subplot(2,1,2);
stem (n,xn);

Xn=fft(xn);
f=linspace(-2*Fs,2*Fs,length(Xn));
figure (2);
plot(f,abs(Xn));
% subplot(2,1,2);
% stem(f,imag(Xn));


