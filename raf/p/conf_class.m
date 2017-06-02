function acc = conf_class(risul, tar, num,classi)
% acc = conf_class(risul, tar, num, classi) calcola sensibilità e specificità a 2 classi
% Confronta il vettore risultati 'risul' con il vettore delle verità 'tar' e fornisce 
% la matrice di confusione dei risultati per il miglior compromesso
% sensibilità/specificità inoltre bisogna indicare il numero di esempi di
% test 'num' ed il numero delle classi del problema

mat = zeros(classi,classi+4);
display(mat);

for d = 1:num  
        z=tar(d);
        zz=risul(d);
        mat(z,zz) = (mat(z,zz))+1;     
end    

display(mat);

for cc = 1:classi   
    for dd = 1:classi 
        mat(cc,6) = mat(cc,dd) + mat(cc,6);
        if (cc~=dd) mat(cc,5) = mat(cc,dd) + mat(cc,5);
        end
        if (cc == dd) mat(cc,6) = mat(cc,dd) + mat(cc,4);
        end
    end
end

        
for xx = 1:classi   
   mat(xx,7) = mat(xx,4)/mat(xx,6) * 100; 
end

accu=0;
tot=0;

for yy = 1:classi   
   accu = (mat(yy,7) + accu)/classi; 
   tot = (mat(yy,6) + tot)/classi; 
   cor = (mat(yy,5) + tot)/classi; 
   sba = (mat(yy,4) + tot)/classi; 
end  

display('Matrice di confusione');
display(mat);

display(accu);

display(cor);

display(sba);

display(tot);
