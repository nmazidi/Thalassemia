train = load('train.mat');
test = load('test.mat');
diagnoseData = load('C:\Users\nmazidi\Documents\Thalassemias\najim\diagnose.mat');
trainX = train.trainX;
trainY = train.trainY;
testX = test.testX;
testY = test.testY;
diagnoseX = diagnoseData.X;

% newrb(P,T,goal,spread,MN,DF) takes two of these arguments,
% P      = R-by-Q matrix of Q input vectors
% T      = S-by-Q matrix of Q target class vectors
% goal   = Mean squared error goal (default = 0.0)
% spread = Spread of radial basis functions (default = 1.0)
% MN	 = Maximum number of neurons (default is Q)
% DF	 = Number of neurons to add between displays (default = 25)

spread = 40;
goal = 0.01;
MN = 20;
DF = 5;

net = newrb(trainX,trainY,goal,spread,MN,DF);
a = sim(net,testX);

thr = 1;
best_thr = 0;
numOfCorrectDiagnoses = 0;
for n = 1:100
    thr = thr + 0.01;
    temp = diagnose(a,size(testX,2),thr);
    num = checkDiagnosis(temp, testY);
    if num > numOfCorrectDiagnoses 
       numOfCorrectDiagnoses = num;
       best_thr = thr;
    end
end
a = sim(net,diagnoseX);
diagnosis = diagnose(a,size(diagnoseX,2), best_thr);

output_res = [a,diagnosis,best_thr];
save rbf_output.dat output_res -ASCII -TABS;