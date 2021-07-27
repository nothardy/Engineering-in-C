%%

%DSP TP N°2 - EJERCICIO 3 FUNCION "FILTER"

% creo una matriz de valores random
y=(1/2)-(1/3)
%%

t=[0:1:15];

b1=1;
a1=[1 -(1/2)];

b2=-1;
a2=[1 -(1/3)];

x1=filter(b1,a1,t);
x2=filter(b2,a2,t);
x=x1

subplot(2,1,1);
plot(t,x1)
subplot(2,1,2);
plot(t,x2)
