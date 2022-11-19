%% Parametros de la profe
%{
K=0.00131;
mc=10/1000;
mb=19/1000;
mm=3.5/1000;
dm=13/100;
dc=4.5/100;
db=8/100;
g=9.81;
I=3e-4;
gamma=0.56;
beta=gamma*2*I;

thop=90;
s=tf('s');
G=(K*dm/I)/(s^2+(beta/I)*s-(((mc*dc-mm*dm-mb*db)/I)*cosd(thop)));
%}

%% Parametros Nuestros
K=0.0008776;
mc=2.07/1000;
mb=7.38/1000;
mm=(3.2+1.28)/1000;
dm=13.1/100;
dc=5/100;
db=4.2/100;
g=9.81;
I=1.1e-4;
gamma=0.575; %valor de la exponencial obtenido en la identificación
beta=gamma*2*I;
