%% PNN Classification per dataset mammografico con rappresentazione
%% attraverso vettore di features di reali...versione con analisi per
%% componenti principali PCA

% Here are three two-element input vectors P and their associated classes Tc.
% We would like to create a probabilistic neural network that classifes these
% vectors properly.

%lettura degli insiemi di addestramento e test

trn=load('C:\MATLAB6p5\work\raf\senza_beta\trainsnzbeta.mat');
tst=load('C:\MATLAB6p5\work\raf\senza_beta\testsnzbeta.mat');

P=trn.X;
Tcc = trn.y;
Tss = tst.y;

%trasformo le etichette dei dati da 0,1,2..  a 1,2,3,.. ovvero la classe dei sani diventa
%da 0 a 1 e le altre vengono traslate di uno

%for k = 1:666
    %Tc(k) = Tcc(k) + 1;    
    %end

%for k = 1:4226
    %Ts(k) = Tss(k) + 1;    
    %end


% Normalizzo i dati con PRESTD (preprocesses the network training set by normalizing the inputs and targets so that
% they have means of zero and standard deviations of 1).
% Inoltre applico l'analisi per componenti principali PCA. La calcolo sul
% train e la applico anche al test

%[pn,minp,maxp] = prestd(P);
%[ptrans,transMat] = prepca(pn,0.02);
%A = transMat*P;
PP = tst.X;         
%PPNN = transMat*PP; 

% Inizio l'analisi con la rete PNN

% First we convert the target class indices Tc to vectors T.  Then we design a
% probabilistic neural network with NEWPNN.  We use a SPREAD value of 1 because
% that is a typical distance between the input vectors.

T = ind2vec(Tcc);

spread = 0.000001;

for d = 1:1000
    
    spread = spread + 0.001;                       % attenzione qui!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    display(spread);
    net = newpnn(P,T,spread);  
    a = sim(net,PP);
    ac = vec2ind(a);
    
    [sen(d), spe(d)] = risul_class(ac, Tss, 99);
end

fpf(1) = 0;
sen2(1) = 0;

for d = 1:1000
    fpf(d) = 1 - spe(d);
    sen2(d) = sen(d);
end 

fpf(1) = 0;
sen2(1) = 0;
fpf(d+1) = 1;
sen2(d+1) = 1;

% Grafico della ROC

figure;
hold on;
plot(fpf,sen2,'red+:');
XLABEL('1 - specificity');
YLABEL('Sensitivity');
TITLE('ROC PNN');
AXIS([0 1 0 1]);
GRID ON;

% Salva su files per calcolo errore della roc

file_roc = [fpf',sen2'];   % file da usare nel calcolo area roc
file_ris= [spe',sen'];     % file per vedere risultati

save pnn_roc.dat file_roc -ASCII -TABS;
save pnn_ris.dat file_ris -ASCII -TABS;