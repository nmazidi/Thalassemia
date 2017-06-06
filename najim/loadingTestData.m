% Read Y values (diagnosys numbers) and X values (haemochromocytometric data)
fid = fopen('test.dat', 'rt');
rawtestdata = textscan(fid, '%*f %*f %*f %*f %f %f %f %f %*f %f %*f %*f %*f %f');
testY = rawtestdata{6};
for n = 1:5
  testX(:,n) = rawtestdata{n};  
end
fclose(fid);
% Write X and Y values to .txt files
fileID = fopen('test.Y','w');
fprintf(fileID, '%d\r\n', testY);
fclose(fileID);
fileID = fopen('test.X','w');
for n = 1:size(testX)
    fprintf(fileID, '%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\r\n', testX(n,:));
end
fclose(fileID);