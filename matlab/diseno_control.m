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

red_tf=(0.2613*s+1)/(0.006074*s+1);
red_tf_discreta=c2d(red_tf, 0.0025, 'tustin');

Ts=1000;
T2=0.0207;
b1=11.24;
a=(Ts*1e-3)+2*T2*b1
b=(Ts*1e-3)-2*T2*b1
c=(Ts*1e-3)+2*T2
d=(Ts*1e-3)-2*T2


