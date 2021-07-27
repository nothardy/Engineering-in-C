%% tp5 ej 1
clc; clear all; close all;
cd('D:\INGENIERIA\año 5\2do cuatrimestre\SISTEMAS CONTROLADOS POR COMPUTADORA\EJERCICIOS MATLAB');
phi=0.3679;
phi2=phi*phi;
gamma=0.6321;
gamma2=gamma*gamma;
q0=0.25;
q1=0.25;
q2=0.5;
N=10;
S=zeros(1,10);
L=zeros(1,10);
S(10)=q0;
X=zeros(1,10);
X(1)=1;
for i=1:9
    S(10-i)=phi2*S(10-i+1)+q1-(((phi*gamma*S(10-i+1))^2)/(gamma2*S(10-i+1)+q2));
    L(11-i)=(gamma*phi*S(10-i+1))/(gamma2*S(10-i+1)+q2);
end
L(1)=(gamma*phi*S(10-10+1))/(gamma2*S(10-10+1)+q2);
k=[1:1:10];
stem(k,L);
Jmin=X(1)*X(1)*S(1);
% para usar esto matricialmente, hay que hacer las phi traspuestas, y el
% vector L va a ser de dos componentes, y S va ser una matriz
%% CASO ESTIMADOr
clc; clear all; close all;
N=100; %DEFINIR NUMERO
K=zeros(1,N);
Pk=zeros(1,N);
R0=1; %cov de xo, es igual a P(0)
r1=1; %covarianza de v
r2=1; %cov de e
desvio=1; %desvio de x(0)
P[0]=


