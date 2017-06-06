testX = load('test.X');
testY = load('test.Y');
trainX = load('train.X');
trainY = load('train.Y');

spread = 25;
goal = 0.01;
MN = 14;
DF = 5;

net = newrb(trainX,trainY,goal,spread,MN,DF);
a = sim(net,testX);