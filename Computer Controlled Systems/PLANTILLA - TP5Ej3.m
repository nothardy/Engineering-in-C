%% SCC - Control optimo
clc; clear all; close all;
cd('D:\INGENIERIA\año 5\2do cuatrimestre\SISTEMAS CONTROLADOS POR COMPUTADORA\EJERCICIOS MATLAB');
%Determinar orden del sistema
phi=[1 1;0 0];
[a,b]=size(phi);
phiT=phi';
gamma=[0; 1];
[c,d]=size(gamma);
gammaT=gamma';
C=[0 1];
CT=C';
%determino los qn segun el ejercicio
q1=CT*C;
ro=0.5;
q0=0.5; 
q2=0.25;
q12=0;
q12T=q12';
%Determino N
N=100;

%Creo vectores S , L , X y X0
X=zeros(a,1,N);
X(:,1,1)=[0.25];               %CONDICION INICIAL - CAMBIA SEGUN EJERCICIO
S=zeros(a,b,N+1);
L=zeros(d,c,N);
u=zeros(c,N);
u(:,1)=0.5;                    %CONDICION INICIAL - CAMBIA SEGUN EJERCICIO

%por definicion s(N)=q0
S(:,:,N+1)=q0;
%comienza bucle for


for i=N:-1:1
    S(:,:,i)=(phiT*S(:,:,i+1)*phi)+q1-(phiT*S(:,:,i+1)*gamma+q12)*((gammaT*S(:,:,i+1)*gamma+q2).^(-1))*(gammaT*S(:,:,i+1)*phi+q12T);
    L(:,:,i)=((q2+gammaT*S(:,:,i+1)*gamma).^(-1))*(gammaT*S(:,:,i+1)*phi+q12T);
end

for i=1:N-1
    X(:,:,i+1)=(phi-gamma*L(:,:,i))*X(:,:,i);
end

%DECLARO VECTOR DE TIEMPOS
t=[1:1:N];



% Calculo J
J=X(:,:,N)'*q0*X(:,:,N);
for i=1:N-1
J=J+X(:,:,i)'*q1*X(:,:,i);+u(:,i)'*q2*u(:,i);
end
Jmin=X(:,:,1)'*S(:,:,1)*X(:,:,1);
%% Graficar X y L caso orden 1

for i=1:N

      X1(i)=X(1,1,i);      % para orden=1
      L1(i)=L(1,1,i);

 end
figure (1)
subplot(2,1,1);
stem(t,X1); title('X');
subplot(2,1,2)
stem(t,L1);;title('L');

%% Graficar X y L caso orden mayor
for i=1:N
     X1(i)=X(1,1,i);
     X2(i)=X(2,1,i);   %solo si es de orden mayor a 1
    L1(i)=L(1,1,i);
    L2(i)=L(1,2,i);


 end

figure(1)
subplot(2,1,1);
stem(t,X1); title('X');
hold on

stem(t,X2)
legend('X1','X2');
 
subplot(2,1,2);
stem(t,L1);title('L');
hold on;
stem(t,L2);
legend('L1','L2');
 
 
 
%% Caso con estimador y ruido

phi=[1 1;0 0];
[a,b]=size(phi);
phiT=phi';
gamma=[0;1];
[c,d]=size(gamma);
gammaT=gamma';
C=[0 1];
CT=C';
R12=0;
R2=0.25;
R1=CT*C;
Varv=0; % Varianza
v=sqrt(Varv)*randn(1,N); % ruido que se suma en los estados.
Vare=0;
e=sqrt(Vare)*randn(1,N); % Ruido que se suma en la salida.
% Defino k, pk, xestimado, y

K=zeros(c,d,N);
%KT=zeros(d,c,N);
Pk=zeros(a,b,N);
R0=[0 1 ; 1 0]; %cov de xo, es igual a P(0)
r1=1; %covarianza de v
r2=1; %cov de e
desvio=1; %desvio de x(0)
Pk(:,:,1)=R0; % defino P(0)=R0
Xest=zeros(a,1,N);
Y=zeros(1,N);
Xest(:,:,1)=[0.5 ;0.5];
Y(1)=C*Xest(:,:,1);

%calculo los pk y los k
for i=1:N
    K(:,:,i)=(phi*Pk(:,:,i)*CT+R12)*((R2+C*Pk(:,:,i)*CT)^(-1));
    %KT(:,:,i)=(phi*Pk(:,:,i)*CT+R12)*((R2+C*Pk(:,:,i)*CT)^(-1));
    Pk(:,:,i+1)=(phi*Pk(:,:,i)*phiT)+R1-(phi*Pk(:,:,i)*CT+R12)*((R2+C*Pk(:,:,i)*CT)^-1)*(C*Pk(:,:,i)*phiT+R12);
end
   
% Estimo los estados con Kalman
for i=2:N
    u(:,i-1)=-L(:,i-1)*Xest(:,:,i-1)';
    Y(i)=C*Xest(:,:,i-1);
    Xest(:,:,i)=phi*Xest(:,:,i-1)+gamma*u(i-1)+K(:,:,i)*(Y(i-1)-C*Xest(:,:,i-1));
end



%Calculo J con ruido
%% Grafico X K Y, de orden=1

for i=1:N

      X1est(i)=Xest(1,1,i);      % para orden=1
      K1(i)=K(1,1,i);

 end
figure (1)
subplot(3,1,1);
stem(t,X1est); title('X estimado');
subplot(3,1,2)
 stem(t,Y); title ('Y')
subplot(3,1,3)
stem(t,K1);title('K');

%% Grafico X K Y, caso orden mayor
for i=1:N
     X1est(i)=Xest(1,1,i);
     X2est(i)=Xest(2,1,i);   %solo si es de orden mayor a 1
    K1(i)=K(1,1,i);
    K2(i)=K(2,1,i);


 end

figure(2)
subplot(3,1,1);
stem(t,X1est); title('X estimado');
hold on

 stem(t,X2est)
 legend('X1','X2');
 subplot(3,1,2)
 stem(t,Y); title ('Y');
 subplot(3,1,3);
 stem(t,K1);title('K');
hold on
 stem(t,K2);
 legend('K1','K2');

