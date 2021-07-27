%% 
clc; clear all;

F=[-2000:0.01:2000];

S=sinc(F);

plot(F,S);
xlim([-10 10]);
ylim([-2 2]);
grid on;

%% Ejercicio 2 - A
clc; clear all;

%                     Calculo de paso de cuantizacion

% Rango
R= 4;
%Niveles
N=128;
%Paso
P=R/N;

% P= 0.0313

%  El error de cuantizacion medio lo considero la mitad del paso.

Ruido=P/2;

% Ruido = 0.0156

%                   Calculo de la relacion señal a ruido de cuantizacion (SNQR)

% Supongo que la señal es senoidal, de amplitud 2 (4Vpp) y frecuencia 5000
% hz
F=5000;
% Declaro el dominio temporal
t= linspace(-100,100,500);
% Declaro la señal
s=2*sin(2*pi*F*t);
% Grafico la señal
figure(1);
plot(t,s)
xlabel('tiempo');
ylabel('señal');
title ('Grafico de la señal');

% Calculo la potencia de la señal
Ps=0;
for i=1:length(t)
    Ps=Ps+(abs(s(i))).^2;
end
Ps=Ps/length(t);

%   Luego, puedo calcular la potencia del ruido de cuantizacion como el
% cuadrado del paso de cuantizacion dividido 12
Pn=((P).^2)/12;
SNQR=Ps/Pn;
%luego, convierto este valor a dB
SNQR=10*log10(SNQR);

% SNQR= 43.8964 dB

% Utilizo la aproximacion para calcular SNQR
bits= 7;
SNQR2= (6.02*bits) +1.76;

% SNQR2= 43.9 dB

%% Ejercicio 2 - Inciso e

clc; clear all


%                     Calculo de paso de cuantizacion

% Rango
R= 4;
%Niveles
N=256;
%Paso
P=R/N;

% P= 0.0156

%  El error de cuantizacion medio lo considero la mitad del paso.

Ruido=P/2;

% Ruido = 0.0078

%                   Calculo de la relacion señal a ruido de cuantizacion (SNQR)

% Supongo que la señal es senoidal, de amplitud 2 (4Vpp) y frecuencia 5000
% hz
F=5000;
% Declaro el dominio temporal
t= linspace(-100,100,500);
% Declaro la señal
s=2*sin(2*pi*F*t);
% Grafico la señal
figure(1);
plot(t,s)
xlabel('tiempo');
ylabel('señal');
title ('Grafico de la señal');

% Calculo la potencia de la señal
Ps=0;
for i=1:length(t)
    Ps=Ps+(abs(s(i))).^2;
end
Ps=Ps/length(t);

%   Luego, puedo calcular la potencia del ruido de cuantizacion como el
% cuadrado del paso de cuantizacion dividido 12
Pn=((P).^2)/12;
SNQR=Ps/Pn;
%luego, convierto este valor a dB
SNQR=10*log10(SNQR);

% SNQR= 49.9170 dB

% Utilizo la aproximacion para calcular SNQR
bits= 8;
SNQR2= (6.02*bits) +1.76;

% SNQR2= 49.92 dB

%% Ejercicio 1- E
clc; clear all;

% Declaro el dominio temporal
t= linspace(-2000,2000,1000);

% Señal 1
s1=cos(4000*pi*t);
% Señal 2
s2=cos(6000*pi*t);

% Grafico de las señales
figure(1)
subplot(2,1,1);
plot(t,s1);
xlabel('tiempo');
ylabel('s1');
title ('Grafico de la señal 1');
subplot(2,1,2);
plot(t,s2);
xlabel('tiempo');
ylabel('s2');
title ('Grafico de la señal 2');










