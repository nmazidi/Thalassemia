dataset = load('dataset.mat');
trainX = dataset.samples;
trainY = dataset.realDiagnosis;

svmStruct = svmtrain(trainX,trainY,'kernel_function','linear');
%xnew = [4.5,5.5;3,6;5.5,2;5.1,3.5];
class = svmclassify(svmStruct,trainX);

numCorrect = 0;
for n=1:390
   if class(n) == testY(n)
       numCorrect = numCorrect + 1;
   end
end
display(numCorrect);
accuracy = numCorrect/390;
accuracy = accuracy*100;
display(accuracy);