function [ diagnosis ] = diagnose( a,num,thr )
for n = 1:num
    if a(n) < thr
        diagnosis(n) = 1; 
    else
        diagnosis(n) = 2;
    end
end
end

