%% DSP - Evaluacion simulacion C2 - 12/06/2019

%%EJERCICIO 1
clc; clear all; close all;


%  Declaramos la señal como una senoidal de amplitud 10 y frecuencia 400
%  Hz.
f=400;
T=1/f;
Fs=1200;
Ts=1/Fs;
t=[-0.1:Ts:0.1];
s=10*sin(2*pi*f*t);

%  Graficamos la señal y su espectro.
 figure(1);
 subplot(2,1,1)
 plot(t,s)
title('Grafico de la señal');xlabel('tiempo');ylabel('s(t)')
S=fftshift(fft(s,length(s))/length(s));
F=linspace(-Fs/2,Fs/2,length(S));
subplot(2,1,2);
plot(F,abs(S));title('Espectro de la señal S(t)'); xlabel('Frecuencia F [Hz]');ylabel ('S(f)');
xlim([-1000 1000]);

%  Declaramos el ruido como 3 senoidales de frecuencia 60,120 y 180 Hz
%  respectivamente.

N=sin(2*pi*60*t)+sin(2*pi*120*t)+sin(2*pi*180*t);
sruido=s+N;
%  Graficamos la señal con ruido agregado, y su espectro.
figure(2)
subplot(2,1,1)
 plot(t,sruido)
title('Grafico de la señal con ruido');xlabel('tiempo');ylabel('s(t) + ruido')
SN=fftshift(fft(sruido,length(sruido))/length(sruido));
F1=linspace(-Fs/2,Fs/2,length(SN));
subplot(2,1,2);
plot(F1,abs(SN));title('Espectro de la señal S(t) con ruido'); xlabel('Frecuencia F [Hz]');ylabel ('S(f) + ruido');
xlim([-1000 1000]);
%% diseño filtro h1

% Diseñamos ambos filtros y comparamos su desempeño.
H1=[0.5 0.5];
H2=[0.5 -0.5];
y1=filter(H1,1,sruido);
y2=filter(H2,1,sruido);

%  Grafico del filtro h1.
figure(3)
freqz(H1,1); title(' respuesta en frecuencia filtro h1');
%  Grafico del filtro h2.
figure(4)
freqz(H2,1); title('respuesta en frecuencia filtro h2');
%  Grafico de la señal filtrada con h1 y su espectro.
figure(5)
subplot(2,1,1)
plot(t,y1);title('Grafico de la salida y1');xlabel('tiempo');ylabel('y1(t)')
Y1=fftshift(fft(y1,length(y1))/length(y1));
F2=linspace(-Fs/2,Fs/2,length(Y1));
subplot(2,1,2);
plot(F2,abs(Y1));title('Espectro de la salida Y1'); xlabel('Frecuencia F [Hz]');ylabel ('Y1(f)');
xlim([-1000 1000]);
%  Grafico de la señal filtrada con h2 y su espectro.
figure(6)
subplot(2,1,1)
plot(t,y2);title('Grafico de la salida y2');xlabel('tiempo');ylabel('y2(t)')
Y2=fftshift(fft(y2,length(y2))/length(y2));
F3=linspace(-Fs/2,Fs/2,length(Y2));
subplot(2,1,2);
plot(F3,abs(Y2));title('Espectro de la salida Y2'); xlabel('Frecuencia F [Hz]');ylabel ('Y2(f)');
xlim([-1000 1000]);

% Vemos que el filtro 2 atenua las componentes del ruido, mientras que el
% filtro 1 no afecta a ninguna de las componentes frecuenciales.

%% EJERCICIO 2
clc; clear all; close all;

%filtro A
Den1=[1,0.030635726430583,0.867612575732375];
Num1= [-9.190982084682560e-04,8.501658428331362e-04];


figure(1)
freqz(Num1,Den1);

% Filtro B
Den2=[1,0.030000000000002,-0.846175000000001];
Num2=[-9.190982084682560e-04,-9.190982084684814e-06,-7.527873876459241e-04];

figure(2)
freqz(Num2,Den2);

%Filtro C

Den3=[1,-0.009999999999999,0.874249999999998];
Num3=[-9.190982084682560e-04,-9.145027174259154e-04];

figure(3)
freqz(Num3,Den3);

%Filtro D
Den4=[1,-0.989999999999998,0.490049999999998];
Num4=[-9.190982084682560e-04,9.236936995105960e-04];

figure(4)
freqz(Num4,Den4);
 
%   Todos los filtros fueron diseñados con la herramienta fdatool, ubicando
%   los polos y ceros segun el enunciado. Luego los exportamos al workspace
%   y guardamos sus componentes. Finalmente, graficamos sus respectivas
%   respuestas en frecuencia, las cuales difieren del enunciado dado que la
%   magnitud no esta normalizada. Sin embargo se observa que los sistemas
%   coinciden con los seleccionados en la evaluacion A4.

