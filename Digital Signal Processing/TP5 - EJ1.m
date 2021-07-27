%% DSP TP5 - EJERCICIO 1

clc; clear all; close all;
f=1000;
T=1/f;
Fs=100000;
Ts=1/Fs;
t=[-0.1:Ts:0.1];
xa=10*sin(2*pi*f*t);
figure(1)
subplot(2,1,1);
plot(t,xa)
xlim ([-0.01 0.01]);
title('Grafico de la señal');xlabel('tiempo');ylabel('xa(t)')
% hago fft
Xa=fftshift(fft(xa,length(xa))/length(xa));
F=linspace(-Fs/2,Fs/2,length(Xa));
subplot(2,1,2);
plot(F,abs(Xa));title('Espectro de la señal xa(t)'); xlabel('Frecuencia F [Hz]');ylabel ('Xa(f)');
xlim([-5000 5000]);
%
w=10*sin(2*pi*60*t); %señal de ruido
x=xa+w;

figure(2)
subplot(2,1,1)
plot(t,x);title(' Grafico de la señal con ruido');xlabel ('tiempo');ylabel('x(t)');
X=fftshift(fft(x,length(x))/length(x));
subplot(2,1,2);
plot(F,abs(X));title('Espectro de la señal con ruido');xlabel('Frecuencia [Hz]');ylabel('X(f)');
xlim([-5000 5000]);



% hay algo mal porque si cambio el t, o el F, el grafico del espectro no
% cae justo en F=1000. Que le cambio?                   
%% Agrego el adc
clc;
figure(3)
subplot(2,1,1);
plot(t,x);title('Grafico del muestreo de la señal mediante un ADC');xlabel('n');ylabel('x[n]');
hold on
Fs2=10000;
Ts2=1/Fs2;
n=[-0.1:Ts2:0.1];


xn=10*sin(2*pi*60*n)+10*sin(2*pi*1000*n);
stem(n,xn)
xlim([-0.001 0.001]);

Xn=fftshift(fft(xn,length(xn))/length(xn));
F=linspace(-Fs2/2,Fs2/2,length(Xn));
subplot(2,1,2);
plot(F,abs(Xn)); title(' Grafico del espectro de la señal muestreada');xlabel ('Frecuencia [Hz]');ylabel('X[f]');

%% Aplico filtro H(z)
clc;
fr=60/Fs;
a=-2*cos(2*pi*(fr));
figure(4);
freqz([1 a 1],1)% tengo que redefinir los a,b del filtro para que me filtre solo la 60/Fs
title('Diagrama de Bode del filtro, con frecuencia normalizada');

% una manera de aplicar el filtro es hacer esta cuenta
for i=3:length(xn)
    y(i)=x(i)+a*x(i-1)+x(i-2);
end
y(1)=x(1);
y(2)=x(2);

%Y=fftshift(fft(y,length(y))/length(y));
%S=Y.*Xn;
%s=ifftshift(ifft(Y,length(Y))/length(y));

% otro metodo es usar el comando filter
s=filter([1 a 1],1,xn);





%% Realizo el DAC
clc;clear sc F;

for i=1:length(s)
    sc(i,:)=y(i).*(sinc((Fs)*(t-i*Ts)));
end

sc=sum(sc);
%sa=conv(s,sinc(Fs*t));
figure(5)
subplot(2,1,1);
plot(t,sc); title(' Señal filtrada reconstruida'); xlabel('Tiempo [t]');ylabel('xa(t)');


%analizo el espectro de sc, donde no deberia haber componentes en 60 hz

SC=fftshift(fft(sc,length(sc))/length(sc));
F=linspace(-Fs/2,Fs/2,length(SC));
subplot(2,1,2);
plot(F,abs(SC));



% Como hago para declarar al filtro?
%% otra manera de calcular Hz(z)
a=-2*cos(2*pi*(60/Fs));
g = tf([1  a 1],[1],Ts);

%como hago


