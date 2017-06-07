train = load('train.mat');
test = load('test.mat');
trainX = train.trainX;
trainY = train.trainY;
testX = test.testX;
testY = test.testY;

% newrb(P,T,goal,spread,MN,DF) takes two of these arguments,
% P      = R-by-Q matrix of Q input vectors
% T      = S-by-Q matrix of Q target class vectors
% goal   = Mean squared error goal (default = 0.0)
% spread = Spread of radial basis functions (default = 1.0)
% MN	 = Maximum number of neurons (default is Q)
% DF	 = Number of neurons to add between displays (default = 25)

spread = 25;
goal = 0.01;
MN = 14;
DF = 5;

net = newrb(trainX,trainY,goal,spread,MN,DF);
a = sim(net,testX);
thr = 0;
for d = 1:1000
   thr = thr + 0.01;
   result = threshold_rbf(a,108,thr);
   [sen(d),spe(d)] = result_class(result, testY, 108);
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

file_ris= [spe',sen'];

save rbf_ris.dat file_ris -ASCII -TABS;