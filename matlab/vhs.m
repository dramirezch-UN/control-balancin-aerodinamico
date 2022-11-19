% conversiones usadas para estimar la TF del vhs
load('vhs.mat');
mag_vhs_abs=db2mag(mag_vhs);
freq_vhs_rads=freq_vhs.*(2.*pi);