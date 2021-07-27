%% COMUNICACIONES  hay que chequear esto
%CÁLCULO DEL ESPECTRO DE UN PULSO RECTANGULAR, UTILIZANDO LA DFT
% Archivo: FIG2_21.M
% Calcule la FFT para un escalón truncado
% Deje que tfin sea el fin del escalón.
M = 7;
N = 2^M;
n = 0:1:N-1;
tfin = 1;
T = 10;
dt = T/N;
t = n*dt;
% Creando la forma de onda de tiempo
w = zeros(length(t),1);
for (i = 1:1:length(w))
if (t(i) <= tfin)
w(i) = 1;
end;
end;
% Calculando la FFT
W = dt*fft(w);
f = n/T;
% Calculando la posición del cuarto nulo 1NULL2
pos = index(f,4/tfin);
plot_pr(2);
plot(t,w);
axis([0 T 0 1.5]);
xlabel('t (sec) -->');
ylabel('w(t)');
title('Forma de onda de tiempo');
pause;
subplot(311);
plot(f(1:pos),abs(W(1:pos)));
xlabel('f (Hz) -->');
ylabel('|W(f)|');
title('ESPECTRO DE MAGNITUD hasta el cuarto nulo 1NULL2');
subplot(312);
plot(f(1:pos),180/pi*angle(W(1:pos)));
xlabel('f (Hz) -->');
ylabel('theta(f) (grados)');
title('ESPECTRO DE FASE hasta el cuarto nulo 1NULL2');
grid;
subplot(313);
plot(f,abs(W));
xlabel('f (Hz) -->');
ylabel('|W(f)|');
title('ESPECTRO DE MAGNITUD sobre rango completo de frecuencias de la FFT');