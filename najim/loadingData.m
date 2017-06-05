% Read Y values (diagnosys numbers) and X values (haemochromocytometric data)
fid = fopen('test.dat', 'rt');
rawdata = textscan(fid, '%*f %*f %*f %*f %f %f %f %f %*f %f %*f %*f %*f %f');
Y = rawdata{6};
for n = 1:5
  X(:,n) = rawdata{n};  
end
% Write X and Y values to .txt files
fileID = fopen('test.Y','w');
fprintf(fileID, '%d\r\n', Y);
fclose(fileID);
fileID = fopen('test.X','w');
for n = 1:size(X)
    fprintf(fileID, '%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\r\n', X(n,:));
end
fclose(fileID);