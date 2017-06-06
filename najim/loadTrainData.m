fid = fopen('training.dat', 'rt');
rawtraindata = textscan(fid, '%*f %*f %*f %*f %f %f %f %f %*f %f %*f %*f %*f %f');
trainY = rawtraindata{6};
for n = 1:5
  trainX(:,n) = rawtraindata{n};  
end
fclose(fid);
% Write X and Y values to .txt files
fileID = fopen('train.Y','w');
fprintf(fileID, '%d\r\n', trainY);
fclose(fileID);
fileID = fopen('train.X','w');
for n = 1:size(trainX)
    fprintf(fileID, '%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\r\n', trainX(n,:));
end
fclose(fileID);