%% DSP - TP4: DFT EJERCICIO 1 inciso A
clc; clear all;
%DTFS
an=0;
x=zeros(1,10);
for k=1:10
    for n=1:8
        an=an+(sin((2*pi*(n-1))./8)*exp(-i*(k-1)*(2*pi*(n-1))./8));
        an=an./8;
    end
    x(k)=an;
    an=0;
end
for k=1:10
    x(k)=abs(x(k));
end
figure(1)
subplot(2,1,1);
n=[0:1:9];
stem(n,x);
xlim([-1 8]);


%DFT
bn=0;
a=zeros(1,8);
for k=1:10
    for n=1:8
        bn=bn+(sin((2*pi*(n-1))./8)*exp(-i*(k-1)*(2*pi*(n-1))./8));
    end
    a(k)=bn;
    bn=0;
end
for k=1:10
    a(k)=abs(a(k));
end
subplot(2,1,2);
n=[0:1:9];
stem(n,a);
xlim([-1 8]);

%% EJERCICIO 1 Inciso B

clc;
clear all;

n=[0:1:7];

xn=sin((2*pi*n)/8);
figure(1);
stem(n,xn);
figure(2);
Xn=fft(xn);
stem(n,abs(Xn));

%% INCISO c


%ahora con n de 0 a 8

clc; clear all;
%DTFS
an=0;
x=zeros(1,10);
for k=1:10
    for n=1:9
        an=an+(sin((2*pi*(n-1))./8)*exp(-i*(k-1)*(2*pi*(n-1))./8));
        an=an./8;
    end
    x(k)=an;
    an=0;
end
for k=1:10
    x(k)=abs(x(k));
end
figure(1)
subplot(2,1,1);
n=[0:1:9];
stem(n,x);
xlim([-1 9]);


%DFT
bn=0;
a=zeros(1,10);
for k=1:10
    for n=1:9
        bn=bn+(sin((2*pi*(n-1))./8)*exp(-i*(k-1)*(2*pi*(n-1))./8));
    end
    a(k)=bn;
    bn=0;
end
for k=1:10
    a(k)=abs(a(k));
end
subplot(2,1,2);
n=[0:1:9];
stem(n,a);
xlim([-1 9]);

n=[0:1:9];
xn=sin((2*pi*n)/8);
figure(2);
stem(n,xn);
figure(3);
Xn=fft(xn);
stem(n,abs(Xn));



