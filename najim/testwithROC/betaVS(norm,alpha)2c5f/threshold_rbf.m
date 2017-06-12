function threshold = threshold_rbf( ac,num,th )
%THRESHOLD_RBF 
%   sets a decision threshold on the value of rbf output neuron
for n = 1:num
    if ( ac(1,n) > th ) 
        threshold(n) = 2;  
    else threshold(n) = 1; 
end

end

