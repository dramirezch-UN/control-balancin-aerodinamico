% Todo lo que se pueda editar estará en este archivo
K=0.0008776;
mc=2.07/1000;
mb=7.38/1000;
mm=(3.2+1.28)/1000;
dm=13.1/100;
dc=5/100;
db=4.2/100;
g=9.81;
I=1.15e-4;
gamma=0.384540871;
beta=gamma*2*I;

load('tiempo_angulo_irl.mat');
exponencial_irl=105.2254188*exp(-0.384540871*tiempo_irl);

s = tf('s');
G=(dm/I)/(s^2+s*beta/I+g*(-dc*mc+dm*mm+db*mb)*cosd(30)/I);
polo_real=4.8036; %obtenido de pole(tf_vhs)
tf_polo_real=K/((1/polo_real)*s+1);
TF=(360/(2*pi))*G*tf_polo_real;
