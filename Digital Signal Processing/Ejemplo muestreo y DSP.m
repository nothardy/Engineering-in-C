%% DSP - ejemplo muestreo y dft

clc; clear all; close all;

%t=linspace(-1000,1000,1000);
t=[-0.001:.00001:0.001];
f=1000;
T=1/f;
Fs=8*f;
Ts=1/Fs;
n=[-0.001:Ts:0.001];
x=10*sin(2*pi*f*t);
xn=10*sin(2*pi*f*n);
figure(1);
plot(t,x);
hold on;
stem(n,xn);
%zero padding
xnzp=zeros(1,4001);
for i=1:length(xn)
    xnzp(i)=xn(i);
end
xn=xnzp;
%% DFT

Xn=fftshift(fft(xn,length(xn))/length(xn));

F=[-2000:1:2000];
figure(2);
plot(F,abs(Xn));

