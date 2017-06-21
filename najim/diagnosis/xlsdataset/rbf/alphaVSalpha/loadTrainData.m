% Read Y values (diagnosys numbers) and X values (haemochromocytometric data)
filename = 'dataset.xls';
rbc = xlsread(filename,'B2:B87');
hb = xlsread(filename,'C2:C87');
hct = xlsread(filename,'D2:D87');
mcv = xlsread(filename,'E2:E87');
rawRealDiagnosis = xlsread(filename,'J2:J87');    %0:normal 1:beta 2:-a/-a 2:-a/aa

 for n = 1:86
    if rawRealDiagnosis(n,1) == 2;
        rawRealDiagnosis(n,1) = 1; 
    else 
        rawRealDiagnosis(n,1) = 2;
    end 
 end

samples(1,:) = rbc;
samples(2,:) = hb;
samples(3,:) = hct;
samples(4,:) = mcv;
realDiagnosis(1,:) = rawRealDiagnosis;

save('dataset.mat','samples','realDiagnosis');
