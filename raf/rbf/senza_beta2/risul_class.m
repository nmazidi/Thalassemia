function [sen, spe] = risul_class(risul, tar, num)
% [sen, spe] = risul_class(risul, tar, num) calcola sensibilit� e specificit� a 2 classi
% Confronta il vettore risultati 'risul' con il vettore delle verit� 'tar' e fornisce i
% parametri sensibilit� sen e specificit� spe a due classi x mammografia;
% bisogna indicare il numero di esempi di test 'num'

num_neg = 0;
for d = 1:num
    if (tar(d) == 1)
        num_neg = num_neg + 1;
    end
end    
num_pos = num - num_neg;    
ris_pos = 0;
ris_neg = 0;

for d = 1:num
   if ((risul(d) == 2) && (tar(d) == 2))
        ris_pos = ris_pos +1;
   end
        
   if ((risul(d) == 1) && (tar(d) == 1))
        ris_neg = ris_neg +1;
   end
end 
    sen = ris_pos/ num_pos;
    spe = ris_neg/ num_neg;
    %end