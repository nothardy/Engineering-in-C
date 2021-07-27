function [  ] = SyE_seno(a,f)
Fs=100000;
Ts=1/Fs;
t=[-0.01:Ts:0.01];
x=a*sin(2*pi*f*t);
X=fftshift(fft(x,length(x))/length(x));
F=linspace(-Fs/2,Fs/2,length(X));
figure(1)
plot(t,x);
figure(2)
plot(F,abs(X));
end

