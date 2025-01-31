train = load('train.mat');
test = load('test.mat');
trainX = train.X;
trainY = train.y;
testX = test.testX;
testY = test.testY;

svmStruct = svmtrain(trainX,trainY,'kernel_function','linear');
%xnew = [4.5,5.5;3,6;5.5,2;5.1,3.5];
class = svmclassify(svmStruct,testX);

numCorrect = 0;
for n=1:99
   if class(n) == testY(n)
       numCorrect = numCorrect + 1;
   end
end
display(numCorrect);
accuracy = numCorrect/99;
accuracy = accuracy*100;
display(accuracy);