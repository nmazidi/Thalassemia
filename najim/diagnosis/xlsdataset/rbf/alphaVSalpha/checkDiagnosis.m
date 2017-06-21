function [ result ] = checkDiagnosis( diagnosis,correctData )
    num = 0;
    for n = 1:86
       if diagnosis(n) == correctData(n) 
          num = num + 1; 
       end
    end
    result = num;
end

