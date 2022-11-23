%% Parametros Root Locust
% solo modificar las siguientes 5 lineas
sobrepico=10; % aka overshoot Mp [porcentaje]
tiempoDeAsentamiento=10; % aka settling time ts [segundos]
tiempoDeElevacion=0.5; % aka rise time tr [segundos]
Kdc=0.006587;
tao=0.001492;

% calculo de z y theta
sobrepico = sobrepico / 100;
zeta=abs((log(sobrepico))/(sqrt((log(sobrepico))^2 + pi^2)));
theta=acosd(z);

a = -4.5/tiempoDeAsentamiento;

radio=1.8/tiempoDeElevacion;

Kp=0.5;
tf_para_rl=(Kdc)/(tao*s^2+(1+Kp*Kdc)*s);% ki variable kp constante


rlocus(tf_para_rl)
hold on
sgrid(zeta, a);
tsline=a+(-1.5e4:0.1:1.5e4)*1i;
viscircles([0 0],radio)
plot(tsline, '--r')
hold off

%% CSD
%controlSystemDesigner(TF);