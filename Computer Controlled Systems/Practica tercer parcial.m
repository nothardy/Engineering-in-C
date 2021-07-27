%% Super codigo 10mil para Sistemas controlados por computadora tercer 
% parcial.
clc; clear all; close all;

%% //////////////////////////////////////////////
% //// Definicion de parametros del sistema: ////
% ///////////////////////////////////////////////
Fi=0.3679;
Gamma=0.6321;
C=1;
D=0;
N=10;
Varv=0; % Varianza
v=sqrt(Varv)*randn(1,N); % ruido que se suma en los estados.
Vare=0;
e=sqrt(Vare)*randn(1,N); % Ruido que se suma en la salida.
[Orden,Orden]=size(Fi);
Q0=0.25;
Q1=0.25;
Q2=0.5; % Debe ser escalar si hay una sola entrada.
Q12=zeros(Orden,Orden);
X0=ones(Orden,1); % Condicion inicial X0
X=zeros(Orden,N); % Vector X contendra los valores de todos los estados en
                  % cada columna por cada instante de tiempo.
L=zeros(Orden,N); % Matriz L contendra los L para cada estado en cada instante
                  % de tiempo.
S=zeros(Orden,N+1);

%% ////////////////////////////////
% //// Calculo del controlador ////
% /////////////////////////////////
S(:,N+1)=Q0;
for i=N:-1:1
    S(:,i)=(Fi'*S(:,i+1)*Fi)+Q1-(Fi'*S(:,i+1)*Gamma+Q12)*((Gamma'*S(:,i+1)*Gamma+Q2)^(-1))*(Gamma'*S(:,i+1)*Fi+Q12');    
    L(:,i)=((Q2+Gamma'*S(:,i+1)*Gamma)^(-1))*(Gamma'*S(:,i+1)*Fi+Q12');
end

%% ///////////////////////////////////////////
% //// En caso de poder medir los estados ////
% //// Calculo la U y la Y                ////
% ////////////////////////////////////////////
% OBSERVACION: En caso de poder medir/calcular los estados, la variable
% PuedoMedirLosEstados debe ser igual a 1. En caso contrario, la variable
% debe ser igual a cero.
% --------------------------
PuedoMedirLosEstados=1; %--
% --------------------------
X(:,1)=X0;
if PuedoMedirLosEstados == 1
    for i=2:N
        X(:,i)=(Fi-Gamma*L(:,i))*X(:,i)+v(:,i);
    end
end

%% //////////////////////////////////////
% //// Calculo del costo J sin ruido ////
% ///////////////////////////////////////
ConozcoElEstadoInicial=1;
CasoDeterministico=1;
if (ConozcoElEstadoInicial == 1)&&(CasoDeterministico==1)
    J=X(:,1)'*S(:,1)*X(:,1);
end

%% //////////////////////////////////////////////////////
% //// Defino los datos para estimar teniendo ruido. //// 
% ///////////////////////////////////////////////////////
X0=ones(Orden,1);
Xest=zeros(Orden,N);
R0=0; % es P(0)
R1=mean(v*v'); % Correlacion del ruido en los estados (v) si son gaussianos
R2=mean(e*e'); % Correlacion del ruido en la salida (e) si son gaussianos
R12=mean(v*e');

%% ///////////////////////////////////////////////////////
% //// Calculo las matrices P y K para la estimacion. //// 
% ////////////////////////////////////////////////////////
P=zeros(Orden,N+1);
K=zeros(Orden,N)';
P(:,1)=0; %= R0
for i=1:N
    K(i,:)=(Fi*P(:,i)*C'+R12)*((R2+C*P(:,i)*C')^(-1));
    P(:,i+1)=(Fi*P(:,i)*Fi')+R1-K(i,:)*(R2+C*P(:,i)*C')*K(i,:)';
end
% Luego estimo los estados.
Xest=zeros(Orden,N);
Y=zeros(N);
U=zeros(1,N);
Xest(:,1)=X0;
for i=2:N
    U(i-1)=-L(:,i-1)*Xest(:,i-1)';
    Y(i)=C*Xest(:,i-1);
    Xest(:,i)=Fi*X(:,i-1)+Gamma*U(i-1)+K(i,:)*(Y(i-1)-C*X(:,i-1));
end

%% ///////////////////////////////////////
% //// Calculo del costo J con ruido ////
% ///////////////////////////////////////
ConozcoElEstadoInicial=1;
TengoRuido=1;
if (ConozcoElEstadoInicial == 1)&&(TengoRuido==1)
    Suma=0;
    for i=1:N:1
        Suma=Suma+S(:,i)*R1;
    end
    J=trace(S(:,1)*R0+Suma);
    sprintf('Costo minimo con ruido: %f',J)
end
% t=1:1:100;
% stem(t,Xest)





