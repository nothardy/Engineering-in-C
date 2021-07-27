%%
% DSP
% tp3: muestreo
% EJERCICIO 1 con Fs=1khz
clc;
clear all;

n=zeros(1,100);
for i=1:100
    n(i)=i;
end


x=5*cos((pi/5)*n)+4*sin(((3*pi)/10)*n); 

%X=fftshift(fft(x));
X=fft(x);
L=length(X);
w=linspace(-pi,pi,L);
stem(w,abs(X));
%plot(w,abs(X),'o')

%%
%Fs=100hz