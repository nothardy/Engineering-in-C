%%  - ejercico tipo parcial
clc; clear all; close all;

fi=[0.78 0;0.22 1];
fi2=fi.*fi;
c=[0 1];
cfi=c*fi;
wo=[c;cfi];
invwo=inv(wo);
k=fi2*invwo*[0;1];
h=0.25;
% Calculo k por ackerman ahora
fit=transpose(fi);
K=acker(fit,c',[0 0]);
gama=[0.22 ;0.03];
xkr(:,1)=[0;0];
uk=[1];
for i=1:10
    xkr(:,i+1)=fi*(xkr(:,i))+gama*uk;
    yr(i)=c*(xkr(:,i));
end

n=[0:0.25:0.25*(length(yr)-1)];
stem(n,yr);

hold on
xks(:,1)=[0;0];
for i=1:10
    xks(:,i+1)=fi*(xks(:,i))+gama*uk+K'*(yr(i)-c*xks(:,i));
    ys(i)=c*(xks(:,i));
end
stem(n,ys)

%debo analizar la diferencia entre los estados, partiendo desde condiciones
%inicales xkr y xks distintas. y ver que al final sean iguales.
