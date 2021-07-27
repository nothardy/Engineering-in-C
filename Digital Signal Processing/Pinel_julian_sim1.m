% Procesamiento Digital de Señales
% Evaluacion Simulacion N° 1
% Alumno: PIÑEL JULIAN
% Legajo: ING -4995

%%
clc;
clear all;

% DEFINO SEÑAL X(t)
t=linspace(-4*pi,4*pi,1024);

F=500;%% es igual a 1/T
x=cos(2*pi*F*t);

%DEFINO funcion de ruido gaussiano, con potencia 0.25

% CALCULO LA POTENCIA DE LA SEÑAL X(T)
LX=length(x);
for i=1:LX
    EX=(abs(x(i))).^2;
end
PX=(1/1024)*EX;
N=wgn(1,1024,0.25*PX);


%defino la y(t) como la suma del ruido mas la funcion x

y=x+N;


%% INCISO A - Graficar x(t), N(t) e y(t);

subplot(3,1,1)
plot(t,x);
xlim([-pi pi]);
xlabel('Tiempo [s]');
ylabel('x(t)');
title('Señal original');
subplot(3,1,2);
plot(t,N);
xlim([-pi pi]);
xlabel('Tiempo [s]');
ylabel('N(t)');
title('Ruido Gaussiano de potencia 0.25 y media cero');
subplot(3,1,3);
plot(t,y);
xlim([-pi pi]);
xlabel('Tiempo [s]');
ylabel('y(t)');
title('Senal x(t) con ruido añadido');

%% INCISO B - MUESTREAR Y(t)

% muestreo la funcion y, definiendo un tiempo de muestreo n=n*Ts
clc;
Fs=5000;
Ts=1/Fs;

n=[0:1:100];
% busco yn
 for i=1:100
     yn(i)=y();
 end
 %%
 stem(n,yn);


%% INCISO C - RECONSTRUIR Y(t). LLAMADA yr(t)

clc;

%defino a la sinc para recuperar la funcion muestreada

gBL=sinc(t*pi*F);

% la funcion reconstruida la obtengo haciendo la convolucion

yr=conv(yn,gBL);
%% INCISO D - aplicar filtro pasabajo

% diseño del filtro
fc1=definir esta frecuencia;
fc2=definir esta frecuencia;
nfiltro=50; %orden del filtro
fdiseho=(2/Fs)*[0 fc1 fc2 Fs/2];
adiseho= [1 1 0 0];
hpb=firpm(50,fdiseho,adiseho); % resp al impulso del pasabanda

HPB=fft(hpb);%% transformo la respuesta al impulso del filtro
Yc=fft(y); %% transformo la señal

Zc=Yc*hpn; % los multiplico en frecuencia

zc=ifft(Zc); %% obtengo z(t)

% muestreo zc para obtener zn, aca el codigo esta vacio porque no se como
% hacerlo via matlab, pero quedaria definida una cierta zn


% para reconstruir zr(t)

zr=conv(zn,gBL);

%% INCISO E

%desconozco el comando para reproducir pero, conociendolo, seria ejecutar
%cada funcion con dicho comando.









