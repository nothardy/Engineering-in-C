%% SISTEMA DE COMUNICACIONES I - TP4 - EJ 1
clc; clear all; close all;

%t=[-0.001:.00001:0.001];

%  Declaro las señales.
Fs=10000000;
Ts=1/Fs;
t=[-0.01:Ts:0.01];
x1=0.1*cos(2*pi*100*t);
x2=0.1*cos(2*pi*455000*t);
x3=x1+x2;
%   Grafico todas las señales, comparo la enorme diferencia de frecuencias.
figure(1)
subplot(3,1,1);
plot(t,x1);title ('Señales x1(t) , x2(t) y la suma de ambas');xlabel('t');ylabel('x1(t)');
subplot(3,1,2);
plot(t,x2);xlabel('t');ylabel('x2(t)');
subplot(3,1,3);
plot(t,x3);xlabel('t');ylabel('x3(t)');
%   Declaro las salidas.
a1=1;a2=2;
y1=(a1*x1)+(a2*(x1.^2));
y2=(a1*x2)+(a2*(x2.^2));
y3=(a1*x3)+(a2*(x3.^2));
%   Grafico las salidas.
figure(2)
subplot(3,1,1);
plot(t,y1);title ('Señales y1(t) , y2(t) , y3(t)');xlabel('t');ylabel('y1(t)');
subplot(3,1,2);
plot(t,y2);xlabel('t');ylabel('y2(t)');
subplot(3,1,3);
plot(t,y3);xlabel('t');ylabel('y3(t)');
%   No nos dice mucho sobre las componentes frecuenciales, analizo ahora sus
%  espectros mediante la DFT.
Y1=fftshift(fft(y1,length(y1))/length(y1));
Y2=fftshift(fft(y2,length(y2))/length(y2));
Y3=fftshift(fft(y3,length(y3))/length(y3));
F=linspace(-Fs/2,Fs/2,length(Y1));
%   Grafico los espectros
figure(3);
plot(F,abs(Y1)); title('Espectro de salida de x1');xlabel('f');ylabel('y1(f)');xlim([-500 500]);
figure(4);
plot(F,abs(Y2));xlabel('f');ylabel('y2(f)');title('Espectro de salida x2')
figure(5);
plot(F,abs(Y3));xlabel('f');ylabel('y3(f)');title('Espectro de salida de x1 + x2')
%% EJ 3
clc; clear all; close all;

fIF=455000;
fc=600000;
fLO=1055000;
fi1=fc+(2*fIF);
fi2=fc-(2*fIF);
%% EJ 7
clc; clear all; close all;
K=1;
fm=1000;
fp1=10000;
Fs=100000;
Ts=1/Fs;
t=[-0.01:Ts:0.01];
m=K*cos(2*pi*fm*t);
p=cos(2*pi*fp1*t);
psen=cos((2*pi*fp1*t)-90);
M=fftshift(fft(m,length(m))/length(m));
F=linspace(-Fs/2,Fs/2,length(M));
figure(1);
subplot(2,1,1);
plot(t,m);title('Señal modulante');xlabel('tiempo [seg]');ylabel('m(t)');
subplot(2,1,2);
plot(F,abs(M));title('Espectro de la señal modulante');xlabel('frecuencia [Hz]');ylabel('M(f)');
%% Inciso B - le sumo una cosenoidal


% espectro en A
mA=m.*p;
MA=fftshift(fft(mA,length(mA))/length(mA));
FA=linspace(-Fs/2,Fs/2,length(MA));
figure(2);
subplot(2,1,1);
plot(t,mA);title('Señal A');xlabel('tiempo [seg]');ylabel('mA(t)');
subplot(2,1,2);
plot(FA,abs(MA));title('Espectro de la señal en A');xlabel('frecuencia [Hz]');ylabel('MA(f)');
%espectro en B
mB=mA+psen;
MB=fftshift(fft(mB,length(mB))/length(mB));
FB=linspace(-Fs/2,Fs/2,length(MB));
figure(3);
subplot(2,1,1);
plot(t,mB);title('Señal en B');xlabel('tiempo [seg]');ylabel('mB(t)');
subplot(2,1,2);
plot(FB,abs(MB));title('Espectro de la señal en B');xlabel('frecuencia [Hz]');ylabel('MB(f)');

%   Espectro en C
mC=mB.*mB;
MC=fftshift(fft(mC,length(mC))/length(mC));
FC=linspace(-Fs/2,Fs/2,length(MC));
figure(4);
subplot(2,1,1);
plot(t,mC);title('Señal en C');xlabel('tiempo [seg]');ylabel('mC(t)');
subplot(2,1,2);
plot(FC,abs(MC));title('Espectro de la señal en C');xlabel('frecuencia [Hz]');ylabel('MC(f)');
%% Filtro la señal en f1=12 khz y f2=27
clear mCf fC filtroC;
mCF=filter(filtro1,mC);
MCF=fftshift(fft(mCF,length(mCF))/length(mCF));
FCF=linspace(-Fs/2,Fs/2,length(MCF));
figure(5);
subplot(2,1,1);
plot(t,mCF);title('Señal en C filtrada');xlabel('tiempo [seg]');ylabel('mCF(t)');
subplot(2,1,2);
plot(FCF,abs(MCF));title('Espectro de la señal en C filtrada');xlabel('frecuencia [Hz]');ylabel('MCF(f)');
%% Espectro de la señal en D
mD=mCF.*mCF;   
MD=fftshift(fft(mD,length(mD))/length(mD));
FD=linspace(-Fs/2,Fs/2,length(MD));
figure(6);
subplot(2,1,1);
plot(t,mD);title('Señal en D');xlabel('tiempo [seg]');ylabel('mD(t)');
subplot(2,1,2);
plot(FD,abs(MD));title('Espectro de la señal en D');xlabel('frecuencia [Hz]');ylabel('MD(f)');
%% filtro nuevamente la señal en D

x=filter(filtro2,mD);
X=fftshift(fft(x,length(x))/length(x));
FX=linspace(-Fs/2,Fs/2,length(X));
figure(7);
subplot(2,1,1);
plot(t,x);title('Señal a la salida');xlabel('tiempo [seg]');ylabel('x(t)');
subplot(2,1,2);
plot(FX,abs(X));title('Espectro de la señal a la salida');xlabel('frecuencia [Hz]');ylabel('X(f)');

