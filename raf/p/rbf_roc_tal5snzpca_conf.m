%% RBF Classification per dataset emocromo per talassemia con rappresentazione
%% attraverso vettore di features di reali...versione con analisi per
%% componenti principali PCA


% Radial basis networks can be used to approximate functions.  NEWRB adds neurons to the hidden layer of a radial basis network
% until it meets the specified mean squared error goal.


%lettura degli insiemi di addestramento e test

trn=load('C:\MATLAB6p5\work\raf\train_tal5.mat');
tst=load('C:\MATLAB6p5\work\raf\test_tal5.mat');

P=trn.X;
Tcc = trn.y;
Tss = tst.y;






% Normalizzo i dati con PRESTD (preprocesses the network training set by normalizing the inputs and targets so that
% they have means of zero and standard deviations of 1).
% Inoltre applico l'analisi per componenti principali PCA. La calcolo sul
% train e la applico anche al test

%[pn,minp,maxp] = prestd(P);
%[ptrans,transMat] = prepca(pn,0.02);
%A = transMat*P;
PP = tst.X;         
%PPNN = transMat*PP; 

%Inizio l'analisi con la rete RBF

% Il parametro di spread deve essere ottimizzato durante la sperimentazione infatti 
% NEWRB(PR,T,GOAL,SPREAD,MN,DF) takes these arguments,
% P      - RxQ matrix of Q input vectors.
% T      - SxQ matrix of Q target class vectors.
% GOAL   - Mean squared error goal, default = 0.0.
% SPREAD - Spread of radial basis functions, default = 1.0.
% MN     - Maximum number of neurons, default is Q.----------------------> nel nostro caso settare max 10% del train
% DF     - Number of neurons to add between displays, default = 25.------> va bene 1..5
% and returns a new radial basis network.

spread = 23;
display(spread);
net = NEWRB(P,Tcc,0.01,spread,3,5);  % addestramento
    
a = sim(net,PP);                   % calcolo risultati sul test
   
% Aggiungo il parametro di soglia th che mi serve per tracciare la curva
% ROC. Uso la funzione soglia_rbf scritta appositamente per leggere i file
% di output  con la probabilità a posteriori calcolata dalla rbf. Calcolo
% quindi i valori di sensibilità e specificità al variare della soglia

th = 1.73;
    
   % for d = 1:1000    
     %   th = th + 0.01; 
        vet_soglia = soglia_rbf(a,108,th);
        [sen, spe] = risul_class(vet_soglia, Tss, 108);
        % end
    


%save rbf_roc.dat file_roc -ASCII -TABS;
%save rbf_ris.dat file_ris -ASCII -TABS;

acc = conf_class(vet_soglia, Tss, 108, 2);
