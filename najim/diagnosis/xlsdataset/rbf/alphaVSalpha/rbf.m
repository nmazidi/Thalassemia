dataset = load('dataset.mat');
trainX = dataset.samples;
trainY = dataset.realDiagnosis;

% newrb(P,T,goal,spread,MN,DF) takes two of these arguments,
% P      = R-by-Q matrix of Q input vectors
% T      = S-by-Q matrix of Q target class vectors
% goal   = Mean squared error goal (default = 0.0)
% spread = Spread of radial basis functions (default = 1.0)
% MN	 = Maximum number of neurons (default is Q)
% DF	 = Number of neurons to add between displays (default = 25)

spread = 40;
goal = 0.01;
MN = 40;
DF = 5;

net = newrb(trainX,trainY,goal,spread,MN,DF);
a = sim(net,trainX);

thr = 1;
best_thr = 0;
numOfCorrectDiagnoses = 0;
for n = 1:100
    thr = thr + 0.01;
    temp = diagnose(a,size(trainX,2),thr);
    num = checkDiagnosis(temp, trainY);
    if num > numOfCorrectDiagnoses 
       numOfCorrectDiagnoses = num;
       best_thr = thr;
    end
end
display(best_thr);
accuracy = (numOfCorrectDiagnoses/86)*100;
display(accuracy);
diagnosis = diagnose(a,size(trainX,2), best_thr);

thr = 0;
for d = 1:1000
   thr = thr + 0.01;
   result = threshold_rbf(a,86,thr);
   [sen(d),spe(d)] = result_class(result, trainY, 86);
end

falsePos(1) = 0;
sen2(1) = 0; 

for n = 1:1000
  falsePos(n) = 1 - spe(n);
  sen2(n) = sen(n);
end 

falsePos(1) = 0;
sen2(1) = 0;
falsePos(d+1) = 1;
sen2(d+1) = 1;

figure;
hold on;
plot(falsePos,sen2,'red+:');
xlabel('1 - specificity');
ylabel('Sensitivity');
title('ROC RBF');
axis([0 1 0 1]);
grid ON;

roc_result= [spe',sen'];
save roc_result.dat roc_result -ASCII -TABS;

output_res = [a',diagnosis',trainY'];
save rbf_output.dat output_res -ASCII -TABS;