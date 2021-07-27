%% 3° parcial SCC - Ejercicio 1 - PIÑEL JULIAN
clc; clear all; close all;
cd('D:\INGENIERIA\año 5\2do cuatrimestre\SISTEMAS CONTROLADOS POR COMPUTADORA\EJERCICIOS MATLAB');
% inciso a - caracteristicas del sistema
%Determinar orden del sistema
phi=[1.45 -0.45;1 0];
[a,b]=size(phi);
phiT=phi';
gamma=[1;0];
[c,d]=size(gamma);
gammaT=gamma';
C=[0.5 0.38];
CT=C';
Wo1=C*phi; % calculo esta componente para determinar en la hoja las caracteristicas del sistema
Wc1=phi*gamma;% calculo esta componente para determinar en la hoja las caracteristicas del sistema
lamda=eig(phi);% determino los autovalores del sistema para analizar estabilidad

%determino los qn segun el ejercicio
q1=CT*C;
q0=0.5; 
q2=0;
q12=0;
q12T=q12';

%Determino N
N=100;

%Creo vectores S , L , X y X0
X=zeros(a,1,N);
X(:,1,1)=[3 ;1];               %CONDICION INICIAL 
S=zeros(a,b,N+1);
L=zeros(d,c,N);
u=zeros(c,N);
u(:,1)=0.5;                    %CONDICION INICIAL 
Y=zeros(1,N);

%por definicion s(N)=q0
S(:,:,N+1)=q0;

%comienza bucle for
for i=N:-1:1
    S(:,:,i)=(phiT*S(:,:,i+1)*phi)+q1-(phiT*S(:,:,i+1)*gamma+q12)*((gammaT*S(:,:,i+1)*gamma+q2).^(-1))*(gammaT*S(:,:,i+1)*phi+q12T);
    L(:,:,i)=((q2+gammaT*S(:,:,i+1)*gamma).^(-1))*(gammaT*S(:,:,i+1)*phi+q12T);
end

for i=1:N-1
    X(:,:,i+1)=(phi-gamma*L(:,:,i))*X(:,:,i);
    Y(i)=C*X(:,:,i);
end
Y(N)=C*X(:,:,N);
%DECLARO VECTOR DE TIEMPOS
t=[1:1:N];
% Calculo J
J=X(:,:,N)'*q0*X(:,:,N);
for i=1:N-1
J=J+X(:,:,i)'*q1*X(:,:,i);+u(:,i)'*q2*u(:,i);
end
Jmin=X(:,:,1)'*S(:,:,1)*X(:,:,1);
%% aDQUIERO VALORES DE  X y L 
for i=1:N
     X1(i)=X(1,1,i);
     X2(i)=X(2,1,i);   
    L1(i)=L(1,1,i);
    L2(i)=L(1,2,i);


end

% Grafico inciso d: estados ; inciso e: salida ; inciso f: accion de control
figure(1)
subplot(3,1,1);
stem(t,X1); title('Estados (X1, X2)');    % Grafico de Estados
hold on

stem(t,X2)
legend('X1','X2');
subplot(3,1,2);
stem(t,Y); title('Salida (Y)');      % Grafico de Salida
 
subplot(3,1,3);
stem(t,L1);title('Acción de control (L)');  % Grafico de accion de control
hold on;
stem(t,L2);
legend('L1','L2');
 
 
 
