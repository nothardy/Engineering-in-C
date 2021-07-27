%%
% DSP TP2: TRANSFORMADA Z
% EJERCICIO 9, INCISO B: CALCULAR Y DIBUJAR LA h[n] UTILIZANDO LA FUNCION
% filter Y COMPARAR CON LA FUNCION impz
clc;
clear all;
%defino el vector de tiempos n
x=zeros(1,50);
x(1)=1;
n=zeros(1,50);
for i=1:50
    n(i)=i;
end
% defino los vectores de numerador y denomiador de la funcion z, con
% b=numerador, a= denominador
b1=[1,0,-1];

a1=[1,0.9,0.6,0.05];

b2=[1,1];

a2=[1,1/4,-1/8];

%aplico la funcion filter

h1=filter(b1,a1,x);
h2=filter(b2,a2,x);

% grafico ambas







% comparo dichos graficos con los que obtengo al aplicar la funcion impz

h11=impz(b1,a1,50,-1);
h22=impz(b2,a2,50,-1);

subplot(4,1,1)
plot(n,h1);

% grafico ambas
subplot(4,1,2)
plot(n,h11);
subplot(4,1,3);
plot(n,h2);

subplot(4,1,4);
plot(n,h22);