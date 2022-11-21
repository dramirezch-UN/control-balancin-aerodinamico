%% Uncompensated phase margin
wx_compensated=wx_specified;
phase_shift_at_wx=rad2deg(angle(evalfr(GP,wx_compensated*1i)));
PMuncompensated=180+phase_shift_at_wx;
%% Determination of phasemax and alphad
phasemax=PMspecified+10-PMuncompensated;
alphad=(1-sind(phasemax))/(1+sind(phasemax));
%% Lead compensator zero and pole
zcd=wx_compensated*sqrt(alphad);
pcd=(zcd)/(alphad);
Gc_lead=((s/zcd)+1)/((s/pcd)+1);
%% Determination of alphag
mag_for_alphag=mag2db(abs(evalfr(Gc_lead,5*1j)*evalfr(GP,5*1j)));
alphag=10^(mag_for_alphag/20);
%% Determination of zcg and pcg
zcg=wx_specified/10;
pcs=zcg/alphag;
Gc_lag=((s/zcg)+1)/((s/pcs)+1);
%% Answer
Gc_lag_lead=Gc_lead*Gc_lag;