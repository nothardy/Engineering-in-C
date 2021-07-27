clear all;close all;clc;

fi=[0.5 1;0.5 0.7];
g=[0.2 ;0.1 ];
c=[1 0];

% t=[1:10];
% sys = ss(fi,g,c,0,[]);
% figure();step(sys,t);%respuesta al escalon del sistema dado en el enunciado (lazo abierto)
% 
% x0=[5 10];% condiciones iniciales de los estados  x1=5   x2=10
% [y,t,x] = initial(sys,x0);t=[1:10];
% x1 =x(1:10,1); x2=x(1:10,2);y=y(1:10);
% figure(),stem(t,y);title('Respuesta a condiciones iniciales');%


%---ackerman

% Pd=roots([1 -0.63 0.21]);
% L = acker(fi,g,[0;0]);
% %al simular este sistema con gama=[0;0] suponemos que la entrada
% %es u=-L*x y desp lo "soltamos " de las condiciones iniciales x0 y se
% %observa en el grafico como la salida va a cero en 2 pasos
% sys = ss(fi-g*L,[0;0],c,0,[]);
% [y,t,x] = initial(sys,x0);

% figure(),stem(y);title('Respuesta a condiciones iniciales');%



%%
nt=100;
u=0;
L= acker(fi,g,[0;0]);
K= acker(fi',c',[0;0]);K=K';

X=[2;3];y(1)=c*X;i=2;
X_=[6 ;10];
for i=2:6
    X=fi*X+g*u; XX(i,:)=X;
    y=c*X; Y(i,1)=y;
   
%observador
    X_=fi*X_+g*u+K*(Y(i-1,1)-c*X_);XX_(i,:)=X_;
%     
%     
    u=-L*X_ 
  end
% figure(),stem([Y XX]),legend('y','x_1','x_2','xest_1','xest_2')

figure(1),stem( XX_),legend('x_1','x_2','xest_1','xest_2')
figure(2),stem(XX(:,1),'ok'),hold,stem(XX_(:,1),'+r'),hold,legend('x','xest')
figure(3),stem(XX(:,1)-XX_(:,1))
return






%%
%*************************Control sobre la perturbacion********************
%inciso a)
%Para poder simular la respuesta del sistema a la perturbaci?n agregamos un
%nuevo estado.Este estado debe ser constante y valer uno.La realimentacion
%de los estados es la misma que antes(dead beat) y a la perturbacion la
%realimentamos de manera de eliminar o minimizar su influecia.

fin=[[fi [1;0]] ;[0 0 1]];
gn=[g;0];
cn=[1 0 0];
Ln=[4 5 5];
sys = ss(fin-gn*Ln,[0;0;0],cn,0,[]);
x0=[5 10 1];%el estado nuevo agregado, que corresponde a la perturbacion lo inicializamos con el valor 1
[y,t,x] = initial(sys,x0);
figure(),stem(y);title('Respuesta a condiciones iniciales');%
%%
%*********************Perturbacion aleatoria*******************************
%Para esta simulaci?n el estado nuevo que agregamos es la entrada aleatoria
%e(k). Entonces; para la ubicaci?n de los polos de los estados, utilizamos
%el mismo resultado de antes que corresponde a un dead beat. Y al estado
%nuevo lo realimentamos con un valor tal que minimice la varianza de la
%salida.

% fin=[[fi [1;0]] ;[0 0 0]];
% gn=[g;0];
% cn=[1 0 0];
% Ln=[L 6];
% sys = ss(fin-gn*Ln,[0;0;1],cn,0,[]);
% u=random('norm',0,1,1,20);
% [y,t] = lsim(sys,u);var(y)
% figure(),lsim(sys,u) 

%%
%inciso b)
%en este caso agregamos un estado, que corresponde al error entre la
%entrada deseada y la salida y despues lo integramos para llevarlo a cero.
clear all;clc;

fi=[0.5 1;0.5 0.7];
g=[0.2 ;0.1 ];
c=[0 1];

fim=[[fi [0;0]] ;[-c 1]];
gm=[g;0];
cm=[c 0];
% % % 
L = acker(fim,gm,[0;0;0]);
% % % 
sys = ss(fim-gm*L,[1;0;0],cm,0,[]);
figure();step(sys);% porque un step?? - - -> xq la entrada de este nuevo sistema es la perturbacion y ?sta es ctte.



%inciso c)
%proximamente (en los mejores cines)

