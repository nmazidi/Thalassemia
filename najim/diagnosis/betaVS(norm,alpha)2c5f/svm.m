train = load('train.mat');
test = load('test.mat');
trainX = train.X;
trainY = train.y;
testX = test.testX;
testY = test.testY;

svmStruct = svmtrain(trainX,trainY, 'ShowPlot',true);