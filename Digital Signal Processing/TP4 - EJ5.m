%% DSP - TP4 EJ 5 a

clc; clear all, close all;
x=[1 2 3 4];

y=[2 -1 1 -1];

N=4;
z=circonv(N,x,y)
%% 5 b
clc; clear all;
close all;

n=[0:7];
x=4.^(-n);
y=cos(3*pi*n*(1/8));
N=8;
z=circonv(N,x,y);

X=fft(x,N);
Y=fft(y,N);
Z=X.*Y;
z2=ifft(Z,N);
z2=transpose(z2)
z3=z-z2

%como z3=z-z2 es cero, ambos metodos para calcular la z son iguales.
%                