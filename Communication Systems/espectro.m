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
R= 4+4;
%Niveles
N=128;
%Paso
P=R/N;

% P= 0.0625


%  El error de cuantizacion medio
