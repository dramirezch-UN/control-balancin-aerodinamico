load('tf_vhs.mat')
bode( TF, tf_vhs*3.6)
legend('simulado', 'vhs*3.6')