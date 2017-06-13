% Read Y values (diagnosys numbers) and X values (haemochromocytometric data)
fid = fopen('test.dat', 'rt');
rawtestdata = textscan(fid, '%*f %*f %*f %*f %f %*f %*f %*f %*f %f %*f %*f %*f %f');
testY(1,:) = rawtestdata{3};
for n = 1:108 
   if testY(1,n) ~= 2;
   testY(1,n) = 1; 
   end 
end
for n = 1:2
  testX(n,:) = rawtestdata{n};  
end
fclose(fid);
save('test.mat', 'testX', 'testY');
% Write X and Y values to .txt files
fileID = fopen('test.Y','w');
fprintf(fileID, '%d\r\n', testY);
fclose(fileID);
fileID = fopen('test.X','w');
for n = 1:size(testX)
    fprintf(fileID, '%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\r\n', testX(n,:));
end
fclose(fileID);