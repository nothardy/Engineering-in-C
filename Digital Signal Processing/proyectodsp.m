%% Prueba filtro DSP
clc; clear all; close all;
cd('D:\INGENIERIA\año 5\1er cuatrimestre\DSP\EJERCICIOS MATLAB');
[x,f]=audioread('guitarsample.wav');
x=x(:,1);
sound(x,f);
Fs=100000;
Ts=1/Fs;
t=linspace(-0.1,0.1,length(x));
subplot(2,1,1);
plot(t,x);title('señal de audio');
X=fftshift(fft(x,length(x))/length(x));
F=linspace(-Fs/2,Fs/2,length(X));
subplot(2,1,2);
plot(F,abs(X));title('espectro de la señal');xlim([-10000 10000]);
%% Defino filtro
filtro=[0.0137766554831583,0.0143926306058812,0.0149995116332086,0.0155955873011437,0.0161791605280998,0.0167485548694469,0.0173021209334144,0.0178382427297485,0.0183553439227064,0.0188518939602944,0.0193264140521214,0.0197774829688356,0.0202037426368476,0.0206039035029029,0.0209767496440577,0.0213211435997206,0.0216360309036504,0.0219204442951345,0.0221735075900149,0.0223944391937629,0.0225825552404305,0.0227372723430126,0.0228581099425320,0.0229446922450029,0.0229967497373241,0.0230141202750950,0.0229967497373241,0.0229446922450029,0.0228581099425320,0.0227372723430126,0.0225825552404305,0.0223944391937629,0.0221735075900149,0.0219204442951345,0.0216360309036504,0.0213211435997206,0.0209767496440577,0.0206039035029029,0.0202037426368476,0.0197774829688356,0.0193264140521214,0.0188518939602944,0.0183553439227064,0.0178382427297485,0.0173021209334144,0.0167485548694469,0.0161791605280998,0.0155955873011437,0.0149995116332086,0.0143926306058812,0.0137766554831583];
load('filtronotch.mat');

%y=filter(filtronotch,x);%notch a=1
Num=[0.121320343559643,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-0.121320343559643];
Den=[1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.757359312880715];
y=filter(Num, Den,x); % notch a=10
figure(2)
subplot(2,1,1);
plot(t,y);title('señal de audio filtrada');
Y=fftshift(fft(y,length(y))/length(y));
F1=linspace(-Fs/2,Fs/2,length(Y));
subplot(2,1,2);
plot(F1,abs(Y));title('espectro de la señal filtrada');xlim([-10000 10000]);
sound(y,f)
%% Flanger
delay=15;
rango=12;
fbarrido=0.3125;
for i=1:(length(x)-rango-delay)
    y(i)=x(i) + x(i + delay + round(rango*sin(2*pi*i*(fbarrido/f))));
end

LY=length(y);
for i=1:length(t)-LY
    y(i+LY)=0;
end

figure(3)
subplot(2,1,1);
plot(t,y);title('señal de audio filtrada con flanger');
Y=fftshift(fft(y,length(y))/length(y));
F1=linspace(-Fs/2,Fs/2,length(Y));
subplot(2,1,2);
plot(F1,abs(Y));title('espectro de la señal filtrada con flanger');xlim([-10000 10000]);
sound(y,f)
