% Read Y values (diagnosys numbers) and X values (haemochromocytometric data)
filename = 'dataset.xls';
rbc = xlsread(filename,'B2:B391');
hb = xlsread(filename,'C2:C391');
hct = xlsread(filename,'D2:D391');
mcv = xlsread(filename,'E2:E391');
rawRealDiagnosis = xlsread(filename,'J2:J391');    %0:normal 1:beta 2:-a/-a 2:-a/aa

samples(1,:) = rbc;
samples(2,:) = hb;
samples(3,:) = hct;
samples(4,:) = mcv;
realDiagnosis(1,:) = rawRealDiagnosis;

save('dataset.mat','samples','realDiagnosis');
