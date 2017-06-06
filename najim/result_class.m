function [sen, spe] = result_class(result, testY, numOfSamples)

num_neg = 0;
for n = 1:numOfSamples
    if (testY(n) == 1)  %if normal
        num_neg = num_neg + 1;
    end
end    
num_pos = numOfSamples - num_neg;    
res_pos = 0;    %number of correct positive results
res_neg = 0;    %number of correct normal results

for n = 1:numOfSamples
   if ((result(n) == 2) && (testY(n) == 2)) %if beta
        res_pos = res_pos +1;  
   end
        
   if ((result(n) == 1) && (testY(n) == 1)) %if normal
        res_neg = res_neg +1;
   end
end 
    sen = res_pos/ num_pos;
    spe = res_neg/ num_neg;
    %end