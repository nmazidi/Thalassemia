% Read Y values (diagnosys numbers) and X values (haemochromocytometric data)
fid = fopen('training.dat', 'rt');
rawtraindata = textscan(fid, '%*f %*f %*f %*f %f %f %f %f %*f %*f %*f %*f %*f %f');
trainY(1,:) = rawtraindata{5};
 for n = 1:178
    if trainY(1,n) ~= 1;
    trainY(1,n) = 2; 
    end 
 end
for n = 1:4
  trainX(n,:) = rawtraindata{n};  
end
fclose(fid);
save('train.mat', 'trainX', 'trainY');
% Write X and Y values to .txt files
fileID = fopen('train.Y','w');
fprintf(fileID, '%d\r\n', trainY);
fclose(fileID);
fileID = fopen('train.X','w');
for n = 1:size(trainX)
    fprintf(fileID, '%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\r\n', trainX(n,:));
end
fclose(fileID);