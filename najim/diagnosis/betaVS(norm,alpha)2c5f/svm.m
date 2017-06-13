train = load('train.mat');
test = load('test.mat');
trainX = train.trainX;
trainY = train.trainY;
testX = test.testX;
testY = test.testY;

svmStruct = svmtrain(trainX,trainY, 'ShowPlot',true);