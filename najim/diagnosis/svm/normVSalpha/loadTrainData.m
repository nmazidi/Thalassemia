% Read Y values (diagnosys numbers) and X values (haemochromocytometric data)
fid = fopen('training.dat', 'rt');
rawtraindata = textscan(fid, '%*f %*f %*f %*f %f %f %f %f %*f %*f %*f %*f %*f %f');
y(:,1) = rawtraindata{5};
 for n = 1:178
    if y(n,1) ~= 1;
    y(n,1) = 2; 
    end 
 end
for n = 1:4
  X(:,n) = rawtraindata{n};  
end
fclose(fid);
save('train.mat', 'X', 'y');
% Write X and Y values to .txt files
fileID = fopen('train.Y','w');
fprintf(fileID, '%d\r\n', y);
fclose(fileID);
fileID = fopen('train.X','w');
for n = 1:size(X)
    fprintf(fileID, '%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\r\n', X(n,:));
end
fclose(fileID);