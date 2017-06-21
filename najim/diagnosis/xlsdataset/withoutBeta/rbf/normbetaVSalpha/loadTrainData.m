% Read Y values (diagnosys numbers) and X values (haemochromocytometric data)
filename = 'dataset.xls';
rbc = xlsread(filename,'B2:B300');
hb = xlsread(filename,'C2:C300');
hct = xlsread(filename,'D2:D300');
mcv = xlsread(filename,'E2:E300');
rawRealDiagnosis = xlsread(filename,'J2:J300');    %0:normal 1:beta 2:-a/-a 2:-a/aa

 for n = 1:299
    if rawRealDiagnosis(n,1) == 2 || rawRealDiagnosis(n,1) == 3;
        rawRealDiagnosis(n,1) = 2; 
    else 
        rawRealDiagnosis(n,1) = 1;
    end 
 end

samples(1,:) = rbc;
samples(2,:) = hb;
samples(3,:) = hct;
samples(4,:) = mcv;
realDiagnosis(1,:) = rawRealDiagnosis;

save('dataset.mat','samples','realDiagnosis');
