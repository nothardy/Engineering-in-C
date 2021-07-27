%% DSP - TP5 EJ 4
clc; clear all; close all;
Fs=1000;
Ts=1/Fs;
n=[-1:Ts:1];
xn=sin(0.1*pi*n)+(1/3)*sin(0.3*pi*n)+(1/5)*sin(0.5*pi*n);
figure(1)
stem(n,xn)
%% inciso a

hn=[1 -2 3 -4 0 4 -3 2 1];

yn=filter(hn,1,xn);

figure(2)
stem(n,yn)

fvtool(hn,1); %visualizo el filtro, veo que distorsiona tanto en magnitud como en fase
%%
f=1000;
a=10;
SyE_seno(a,f)