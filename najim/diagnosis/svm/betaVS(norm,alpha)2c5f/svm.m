train = load('train.mat');
test = load('test.mat');
trainX = train.X;
trainY = train.y;
testX = test.testX;
testY = test.testY;

svmStruct = svmtrain(trainX,trainY, 'ShowPlot',true);
xnew = [4.5,5.5;3,6;5.5,2;5.1,3.5];
class = svmclassify(svmStruct,xnew,'ShowPlot',true);
