%controlSystemDesigner('bode' ,TF);
z=tf('z');
T=0.01;
%control=(29.102*(s+275.7)*(s+2.216)*(s^2 + 2.772*s + 61.43))/(s*(s+254.2)*(s^2+41.33*s+814.8));
%control=(1.4728 *(s+275.7)* (s+2.216)* (s^2 + 2.772*s + 61.43))/(s*(s+254.2)* (s^2 + 41.33*s + 814.8));
%control=(1.1488 *(s+275.7)* (s+2.216)* (s^2 + 2.772*s + 61.43))/(s*(s+254.2)* (s^2 + 41.33*s + 814.8));
control=(12.409 *(s+275.7)* (s+0.6775)* (s^2 + 2.772*s + 61.43))/(s* (s+254.2)* (s^2 + 41.33*s + 814.8));
control_discreto=c2d(control,T,'tustin')

step(control, control_discreto,1)
legend('control continuo', 'control discreto')


