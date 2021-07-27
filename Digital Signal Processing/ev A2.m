%% DSP Evaluacion A2
%PIÑEL JULIAN  ING - 4995
%% EJERCICIO 1
clc; 
clear all;

xn=[1 3 2 -2];
% declaro a xc(1.5) como xc, para poder utilizarlo en una sumatoria
xc=0;
%Realizo la suma de convolucion para el valor t=1.5
for i=1:4
    xc=xc+xn(i)*(sin(pi*(1.5-(i-1)))./(pi*(1.5-(i-1))));
end
%% EJERCICIO 2 - INCISO A
clc;
clear all;

t=linspace(-1000,1000,1000);
xc=5*sin(10000*pi*t-(pi/2));
plot(t,xc);

rango=10;%el rango maximo de valores va de -5 a 5 dado que los valores de una senoidal estan acotados
b=8; % trabaja con 8 bits
paso=rango/2^b;

%el paso de cuantizacion es 0.0391

%la relacion señal a ruido se puede aproximar como

SNQR=6.02*b+1.76;
Ps=0;
%podemos tambien calcularla como la potencia de la señal, dividido la
%potencia del ruido, en dB

%primero calculo la potencia de la señal, haciendo la sumatoria del valor
%absoluto de cada componente al cuadrado, luego lo divido por el intervalo
%de tiempo que le di a la señal. Esta seria una aproximacion numerica
%bastante fiable de la potencia de la señal
for i=1:length(t)
    Ps=Ps+(abs(xc(i))).^2;
end
Ps=Ps/length(t);
%Luego, puedo calcular la potencia del ruido de cuantizacion como el
% cuadrado del paso de cuantizacion dividido 12
Pn=((paso).^2)/12;
SNQR2=Ps/Pn;
%luego, convierto este valor a dB
SNQR2=10*log10(SNQR2);

%el valor obtenido es tan cercano al estimado, que puedo considerar que son
%iguales para los fines practicos. Por lo tanto el resultado obtenido es
%correcto.

%% EJERCICIO 2 - INCISO B

%En este inciso debo obtener la señal recontruida para dos casos: en uno
%tomo en cuenta el error de cuantizacion y en el otro no.

%cabe aclarar que la señal reconstruida sufrira aliasing dado que la
%frecuencia de muestreo es inferior al doble de la frecuencia maxima de la
%señal.
clc;
clear all;

F=5000;
Fs=8000;
T=1/F;
Ts=1/Fs;

t=[-10*T:0.00001:10*T];
xc=5*sin(2*pi*F*t-(pi/2));
figure(1)
plot(t,xc);
hold on;

%obtengo la señal muestreada xn
n=[-10*T:Ts:10*T];
xn=5*sin((F*2*pi*n)-((pi)/2));
stem(n,xn)

%declaro la sinc para reconstruir
gBL=sinc(t*Fs);
figure(2);
plot(t,gBL);
xr=conv(xn,gBL);
figure(3);
subplot(2,1,1);
plot(t,xc);
xlabel('tiempo');
ylabel('xc');
title('señal original');
t2=linspace(-10*T,10*T,433);%
subplot(2,1,2);
plot(t2,xr);
xlabel('tiempo');
ylabel('xr');
title('señal reconstruida');
xlim([-3*T,3*T]);



%Vemos que en un periodo la señal queda una senoidal de 3000 Hz. Fuera de
% esos limites la señal ya queda totalmente distorsionada. Todo esto es
% producto del aliasing por no cumplir el teorema del muestreo.

%% ahora hacemos la reconstruccion con el error de cuantizacion
t=[-10*T:0.00001:10*T];

%cuantizo los valores de la xn
xncuant=(127/5)*xn;

%redondeo los valores de la cuantizacion

xncuantred=int8(xncuant);

%%transformo los valores redondeados a tipo double para poder realizar
%%convolucion cpon codigo

xnred=double(xncuantred);

%vuelvo a dejar los valores redondeados en valores equivalentes

xn2=(5/127)*xnred;

%declaro la sinc para reconstruir
gBL=sinc(t*Fs);
xrcuant=conv(xn2,gBL);
figure(3);
subplot(3,1,1);
plot(t,xc);
xlabel('tiempo');
ylabel('xc');
title('señal original');
t2=linspace(-10*T,10*T,433);
subplot(3,1,2);
plot(t2,xr);
xlabel('tiempo');
ylabel('xr');
title('señal reconstruida');
xlim([-3*T,3*T]);
subplot(3,1,3);
plot(t2,xr);
hold on;
plot(t2,xrcuant);
 xlabel('tiempo');
 ylabel('xrcuant');
  title('señal reconstruida con error de cuantizacion vs señal reconstruida sin cuantizar');
xlim([-3*T,3*T]);

figure(4)
diferencia=xrcuant-xr;
plot(t2,diferencia);
xlabel('tiempo');
 ylabel('xrcuant-xr');
  title('error de cuantizacion punto a punto');
  xlim([-3*T,3*T]);





