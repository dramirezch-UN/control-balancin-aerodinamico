load('test_ref_30.mat')
load('test_ref_80.mat')
%%load('test_ref_100.mat')

sim('simulacion_test.slx',20)

% figure("Name", "test 30")
% plot(ans.test_30.time,ans.test_30.data, t_test_30, ang_test_30)
% xlabel tiempo[segundos]
% ylabel angulo[grados]
% grid minor
figure("Name", "test 80")
plot(t_test_800, ang_test_800)
grid minor
% figure("Name", "test 100")
% plot(ans.test_100.time,ans.test_100.data,t_test_200, ang_test_200)
% grid minor


