%% DSP -  Evaluacion A2
%% Alumno:PIÑEL JULIAN  
%% LEGAJO:  ING - 4995
%% EJERCICIO 1
clc; 
clear all;

xn=[1 3 2 -2];
%   Declaro a xc(1.5) como xc, para poder utilizarlo en una sumatoria.
xc=0;
%   Realizo la suma de convolucion para el valor t=1.5
for i=1:4
    xc=xc+xn(i)*(sin(pi*(1.5-(i-1)))./(pi*(1.5-(i-1))));
end


%% EJERCICIO 2 - INCISO A
clc;
clear all;

t=linspace(-1000,1000,1000);
xc=5*sin(10000*pi*t-(pi/2));
plot(t,xc);

%   El rango maximo de valores va de -5 a 5 dado que los valores de una
% senoidal estan acotados.
rango=10;

% Trabaja con 8 bits.
b=8; 

%  Calculo el paso de cuantizacion utilizando la formula del libro.
paso=rango/2^b;

%  El paso de cuantizacion es 0.0391.

%  La relacion señal a ruido se puede aproximar de la siguiente manera.

SNQR=6.02*b+1.76;
Ps=0;

%El valor dio aproximadamente 50 dB.

%   Podemos tambien calcularla como la potencia de la señal, dividido la
% potencia del ruido, en dB. Este paso para verificar la aproximacion no lo
% hice en la evaluacion escrita dado que no tenia el tiempo suficiente.
%  Ahora me servira para verificar dicho valor.

%   Primero calculo la potencia de la señal, haciendo la sumatoria del valor
% absoluto de cada componente al cuadrado, luego lo divido por el intervalo
% de tiempo que le di a la señal. Esta seria una aproximacion numerica
% bastante fiable de la potencia de la señal.

for i=1:length(t)
    Ps=Ps+(abs(xc(i))).^2;
end
Ps=Ps/length(t);

%   Luego, puedo calcular la potencia del ruido de cuantizacion como el
% cuadrado del paso de cuantizacion dividido 12
Pn=((paso).^2)/12;
SNQR2=Ps/Pn;
%luego, convierto este valor a dB
SNQR2=10*log10(SNQR2);

%   Nuevamente da aproximadamente 50 dB

%   El valor obtenido es tan cercano al estimado, que puedo considerar que son
% iguales para los fines practicos. Por lo tanto el resultado obtenido es
% correcto.

%% EJERCICIO 2 - INCISO B

%   En este inciso debo obtener la señal recontruida para dos casos: en uno
% tomo en cuenta el error de cuantizacion y en el otro no.

%   Cabe aclarar que la señal reconstruida sufrira aliasing dado que la
% frecuencia de muestreo es inferior al doble de la frecuencia maxima de la
% señal, es decir, no cumple con las hipotesis del Teorema del Muestreo.
clc;
clear all;

F=5000;
Fs=8000;
T=1/F;
Ts=1/Fs;
limt=100/F;

t=[-10*T:0.00001:10*T];
xc=5*sin(2*pi*F*t-(pi/2));

%   Obtengo la señal muestreada xn.
n=[-limt*F:1:limt*F];
xn=5*sin((F*2*pi*n*Ts)-(pi/2));

%   Defino el tiempo para la funcion sinc.
t2=[-limt:1/(500*F):limt];

%   Realizo la convolucion entre la señal muestreada y la sinc.

for i=1:1:length(xn)
    xr(i,:)=xn(i)*(sinc((Fs)*(t2-i*Ts)));
end
xr=sum(xr);
t3=linspace(-limt,limt,length(xr));

%   Una vez que obtuve la señal reconstruida, grafico la señal original y la
% reconstruida.
figure(2);
subplot(2,1,1);
plot(t,xc);
xlabel('tiempo');
ylabel('xc');
title('señal original');
subplot(2,1,2);
plot(t3,xr);
xlabel('tiempo');
ylabel('xr');
title('señal reconstruida');
xlim([0,0.005]);

%   Calculo la frecuencia de la señal reconstruida.
frec=1/(0.002952-0.002617);

%   Este valor es aproximadamente 3 Khz.




%   Vemos que la señal reconstruida senoidal de 3000 Hz. Esto es
% producto del aliasing por no cumplir el teorema del muestreo.

%% Ahora hacemos la reconstruccion considerando el Error de Cuantizacion

%   Cuantizo los valores de la xn, elijo 127 dado que la cant maxima de bits
% es 2^8=256.
xncuant=(127/5)*xn;

%   Redondeo los valores de la cuantizacion con la funcion int8.

xncuantred=int8(xncuant);

%   Transformo los valores redondeados a tipo double para poder realizar
% la convolucion con codigo.

xnred=double(xncuantred);

%   Vuelvo a dejar los valores redondeados en valores equivalentes

xn2=(5/127)*xnred;

%   Realizo la convolucion entre la señal muestreada y la sinc.

for i=1:1:length(xn2)
    xr2(i,:)=xn2(i)*(sinc((1/Ts)*(t2-i*Ts)));
end
xr2=sum(xr2);
t4=linspace(-limt,limt,length(xr2));

%   Una vez que obtuve la señal reconstruida, grafico la señal original, la
% reconstruida y un tercer grafico con la señal reconstruida sin error de
% cuantizacion y la señal reconstruida con error de cuantizacion.
figure(3);
subplot(3,1,1);
plot(t,xc);
xlabel('tiempo');
ylabel('xc');
title('señal original');
subplot(3,1,2);
plot(t4,xr2);
xlabel('tiempo');
ylabel('xr');
title('señal reconstruida');
xlim([0,0.005]);
subplot(3,1,3);
plot(t4,xr);
hold on;
plot(t2,xr2);
 xlabel('tiempo');
 ylabel('xrcuant');
  title('reconstruccion con error de cuantizacion vs reconstruccion sin cuantizar');
xlim([0,0.005]);

%   Para que sea mas visual, grafico la diferencia entre ambas.
figure(4)
diferencia=xr2-xr;
plot(t2,diferencia);
xlabel('tiempo');
ylabel('xr2-xr');
title('error de cuantizacion punto a punto');
xlim([0,0.005]);
  
%   Aplicando mucho zoom al grafico donde estan ambas señales
% reconstruidas, veo el error de cuantizacion, el cual es muy pequeño.

%   En el grafico de la figura 4, puedo apreciar el error de cuantizacion
% punto a punto. En algunos casos ambas funciones van a coincidir, es
% decir, el error sera 0; asimismo, en otros casos el error será mayor.

  





