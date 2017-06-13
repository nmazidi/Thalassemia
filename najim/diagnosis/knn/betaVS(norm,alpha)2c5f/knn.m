train = load('train.mat');
test = load('test.mat');
trainX = train.X;
trainY = train.y;
testX = test.testX;
testY = test.testY;

mdl = fitcknn(trainX,trainY,'NumNeighbors',23,'Standardize',1);
xnew = [6,5];
label = predict(mdl,xnew);
display(label);