
/***********************************************************/
/*                        k-NN                             */
/*  Classification algorithm based on the K neighborhoods  */
/*                                                         */
/*  Ties are randomly broken                               */
/*                                                         */
/*  Version 26/02/1997                                     */
/*  by Giorgio Giacinto                                    */
/*  DIEE-UNICA                                             */
/***********************************************************/

/** Modificato per dati sulla Talassemia da GianLuca Masala il 05/03/2002
	Le modifiche sono date  dal formato dei files di training, ora del tipo
	<label> <label-classe/i> <feature>


/**** Questo file contiene delle modifiche apportate al file 
      originale da Stefano Pusceddu. 
      Le modifiche riguardano la possibilita' di inviare al programma
      al momento dell'esecuzione due valori che individuino un range
      per k; il programma calcola una sola volta le distanze fra il test
      pattern e i training patterns, dopodiche' le sfrutta per tutti i 
      valori di k all'interno del range scelto: il fatto di poter effet-
      tuare una sola volta per tutte il calcolo delle distanze (passaggio
      molto lungo in termini di tempo), nonche' il riordino di tali distanze
      per ogni test pattern,  rende la soluzione qui proposta preferibile ad
      una esecuzione ripetuta del programma originale con lancio di file batch

      Si ottengono tanti files d'uscita quanti sono i valori di k utilizzati.
      Si e' aggiunto inoltre un file d'uscita per ogni valore di k su cui
      vengono memorizzate le probabilita' a posteriori, necessarie per l'algo-
      ritmo di selezione.
*******************************************************************************/      

#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define QUAD(a)    (a)*(a)
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MAXCLASS 20
#define MAXCAMP 100000
#define MAXCAR 50
#define MAXVAL 2147483647
#define MAXK 1000
#define RANGE 100 

struct pattern
  {
    double val;
    int classe;
    int pos;
  };

/*
   This structure is used for distances storing.
   Given one pattern to be tested, we have to store the distances
   between the test pattern and all the training patterns. This is done
   by means of an array of stuctures, one for each training pattern. In order
   to keep all the information necessary to classify the test pattern
   this structure contains:
   - the distance of the test pattern from one the training pattern <val>;
   - the level of risk class the training pattern belongs to <class>;
   - a number with the position of the considered training pattern in the
     input data file <pos> (so if necessary it is easy to recover more information 
     about the neighborhood).
*/


/*
   FUNCTION PROTOTYPES
*/
void calcdist(int camp); 
int daiclasse(char ch);
void stampaConfusione(FILE *file,  char* stringaClassi,int nT,int K);
void file_open(char **argv);
void parse(int argc,char **argv);
void calcdist(int camp);
void  QSricors(struct pattern *vett, int  inf, int  sup);
void classif(int camp, int K);
void init_random();
void  quicksort(struct pattern *vett, int  grand);
void itostr(char *stringa, int num, int max_exp);

/*
   VARIABLES DECLARATION
*/

double *texset;                   /* Training set patterns            */
double *trnset;                   /* Test set patterns                */
int *targatr;                     /* Truth for training patterns      */
int *targatx;                     /* Truth for test patterns          */
int *targatxseconda;
int *count_tr;                    /* # of tr patterns for each class  */
int count_tx[RANGE][MAXCLASS];                    /* # of tx patterns for each class  */
char **nametr;                    /* labels of training patterns      */
char **nametx;                    /* Labels of test patterns          */
struct pattern *dist;             /* Distances between a test pattern 
                                     and training patterns */
double perc;
int ntrs;                         /* total # of tr patterns           */
int ntxs;                         /* total # of tx patterns           */
int nfeat;                        /* # of features                    */
int Kmin;                         /* value of min K parameter         */
int Kmax;                         /* value of max K parameter         */
int nclass;                       /* # of classes                     */
int conperc[RANGE];               /* # of misclassified patterns for each
                                     value of K */
int perclass[RANGE][MAXCLASS][MAXCLASS];    /* # of correctly classified patterns
                                     for each class and for each value of K*/
double zz;                        /* dummy                            */
int contarand;                    /* # of random choices              */
char nomeout[MAXCAR];             /* output file                      */
double peso;

FILE *fintrns,*fintxs;            /* pointers to data files           */
FILE *fout[RANGE],*fout2[RANGE];  /* pointers to output files
                                     ora fout e' un vettore di pointers 
                                     a files; fout2 e' un vettore di pointers 
                                     a files su cui verranno memorizzate le
                                     probabilita' a posteriori */

FILE *fres;                                             



/*
   MAIN
*/

void stampaConfusione(FILE *file,  char* stringaClassi,int nT,int K)
{
  register int i,j;
  unsigned int totOK=0,tot=0;
  unsigned int ni[10];


  for(i=0;i<nT;i++)
    fprintf(file," %6c",stringaClassi[i]);


  fprintf(file,"      OK   BAD  TOT  ACC\n");

  for(i=0;i<nT+6;i++)
    fprintf(file,"------");
  fprintf(file,"-");

  for(i=1;i<=nT;i++) {
    for(j=1,ni[i]=0;j<=nT;j++)
      if(i!=j) ni[i] += perclass[(K-Kmin)/2][i][j];

    totOK += perclass[(K-Kmin)/2][i][i];
    tot += perclass[(K-Kmin)/2][i][i]+ni[i];
  }

  for(i=1;i<=nT;i++) {
    fprintf(file,"\n %c |",stringaClassi[i-1]);

    for(j=1;j<=nT;j++) {
      fprintf(file," %6.2f",(((float)perclass[(K-Kmin)/2][i][j])/((float)(perclass[(K-Kmin)/2][i][i]+ni[i])))*100.);
    }
    if(ni[i]+perclass[(K-Kmin)/2][i][i]>0)
      fprintf(file," %4d %4d %4d %6.2f%%",
	    perclass[(K-Kmin)/2][i][i],
       ni[i],
        ni[i]+perclass[(K-Kmin)/2][i][i],
	(((float)perclass[(K-Kmin)/2][i][i])/((float)(ni[i]+perclass[(K-Kmin)/2][i][i])))*100.);
    else
      fprintf(file," %4d %4d %4d   -.-%%",
	    perclass[(K-Kmin)/2][i][i],
       ni[i],
        ni[i]+perclass[(K-Kmin)/2][i][i]);
  }

  fprintf(file,"\n   |");

  for(j=1;j<=nT;j++)
    fprintf(file,"       ");
  fprintf(file," %4d %4d %4d %6.2f%%",
	  totOK,tot-totOK,tot,
	  ((float)totOK/((float)tot)*100));



  fprintf(file,"\n\n\n");
  fprintf(file,"  Accuracy    : %5.2f%%\n",((float)totOK/(float)tot)*100.);
  fprintf(file,"\n");
}	


int main(int argc,char **argv)
{
  int i, j, K,co,volte;   /* K e' il valore attuale del vicinato */
  FILE *fp;


  parse(argc,argv);             /* data input                        */
  init_random();

    /* si inizializzano le variabili di conteggio per le classificazioni
       corrette e scorrette */
  for(K=Kmin;K<=Kmax;K+=2)  {

     conperc[(K-Kmin)/2]=0;

     for(i=0;i<MAXCLASS;i++)
       for(j=0; j<MAXCLASS; j++)
        perclass[(K-Kmin)/2][i][j]=0;
   }


    /* si analizza un test pattern alla volta; per esso si calcolano le
       distanze dai training patterns e le si ordina; si inizia poi un ciclo
       in cui il test pattern in uso viene classificato per tutti i valori
       di k; si memorizzano poi (operazione svolta da 'classif') le informazioni
       parziali che alla fine dell'analisi su tutti i test patterns serviranno
       per valutare il metodo */
  for(i=0;i<ntxs;i++)   {

     /* calcola le distanze del test pattern da tutti i training patterns
        e le memorizza nel vettore di strutture 'dist' */
   calcdist(i);

     /* Training patterns are reordered from the nearest to the farthest */
   quicksort(dist,ntrs);

 /* ciclo in cui si classifica ripetutamente il pattern al variare di K
    (k viene incrementato di 2 ad ogni giro per mantenerlo sempre dispari) */
   for(K=Kmin;K<=Kmax;K+=2)
   {
   	//for(co=0; co<nclass; co++) count_tx[(K-Kmin)/2][co]=0;
	classif(i, K);
   }

  }


 for(K=Kmin;K<=Kmax;K+=2)  {
    fprintf(fres," K = %d    \n",K); /* 'fres' points to a file where
                                       summary results are written.
                                       Useful with different 'k' values
                                       on the same data set           */
    perc=100-(float)conperc[(K-Kmin)/2]*100/(float)ntxs;
    fprintf(fres,"\n% OF TOTAL CORRECT DECISIONS: %5.2f %%\n",perc);
    fp=fopen("ris.k","a");
    fprintf(fp,"%.2f\n",perc);
    fclose(fp);
    fp=fopen("k.k","a");
    fprintf(fp,"%d\n",K);
    fclose(fp);
    stampaConfusione(fres,"NAB",nclass,K);
/*        for (i=0;i<nclass;i++)
          {
            //printf("%d %d\n",i,count_tx[(K-Kmin)/2][i]);
            if (perclass[(K-Kmin)/2][i+1] != 0)
               zz=perclass[(K-Kmin)/2][i+1]*100.0/count_tx[(K-Kmin)/2][i];
            else
	       zz=0;
            fprintf(fres,"% OF CORRECT DECISION FOR THE CLASS # %d = %5.2f %%\n",i+1,zz);
          }*/

	fprintf(fres,"\n\n");


 }
  return 0;
}


/*
   PARSE: allocation of input data
*/

int daiclasse(char ch)
{
	switch(ch)
	{
		case 'N': return 1;
		case 'A': return 2;
		case 'B': return 3;
	}
	return 0;
}

char dailabel(int i)
{
	switch(i)
	{
		case 1 : return 'N';
		case 2 : return 'A';
		case 3 : return 'B';
	}
	return ' ';
}

void parse(int argc,char **argv)
{
  int i,j,c,k[MAXCLASS];
  char classe[10];

  if (argc != 12)
     {
	printf("\n%s  <peso > <trset> <txset> <nclass> <ntrs> <ntx> <nft> <K> <fout> <fout2>", argv[0]);
	puts("\n\n   <peso>   : valore con il quale si pesa la prima metà delle feature");
	puts("\n\n   <trset>  : name of the file containing the training set ");
	puts("\n   <txset>  : name of the file containing the test set ");
	puts("\n   <nclass> : number of classes ");
	puts("\n   <ntrs>   : number of the training set patterns ");
	puts("\n   <ntx>    : number of the test set patterns ");
	puts("\n   <nft>    : number of features");
	puts("\n   <Kmin>   : min dimension of the neighborhood "); 
	puts("\n   <Kmax>   : max dimension of the neighborhood "); 
	puts("\n   <fout>   : common name of the output files "); 
	puts("\n   <fout2>  : common name of the output files No.2 \n"); 
	exit(0);  /* ora per fout viene letto il prefisso comune dei nomi
                     dei files d'uscita e per fout2 viene letto il prefisso
                     comune dei files d'uscita in cui verranno memorizzate
                     le probabilita' a posteriori delle varie classi per ogni 
                     pattern */
     }
   
file_open(argv);      /* reads input data from command line           */
                      /* follows: memory allocation functions         */

     	if ((trnset=(double*)malloc(ntrs*nfeat*sizeof(double))) ==NULL)
       		{
       		puts("\n   Memory allocation error (1)\n");
       		exit(-1);
       		}
	
     	if ((nametr=(char **)malloc(ntrs*sizeof(char *))) ==NULL)
		{
       		puts("\n   Memory allocation error (2)\n");
       		exit(-1);
		}
        for(i=0;i<ntrs;i++)
     	if ((nametr[i]=(char *)malloc(MAXCAR*sizeof(char))) ==NULL)
		{
       		puts("\n   Memory allocation error (3)\n");
       		exit(-1);
		}
			
     	if ((targatr=(int*)malloc(ntrs*sizeof(int))) ==NULL)
       		{
       		puts("\n   Memory allocation error (4)\n");
       		exit(-1);
       		}
	
     	if ((count_tr=(int*)calloc(nclass, sizeof(int))) ==NULL)
       		{
       		puts("\n   Memory allocation error (5)\n");
       		exit(-1);
       		}

     	if ((texset=(double*)malloc(ntxs*nfeat*sizeof(double))) ==NULL)
        {
         puts("\n   Memory allocation error (6)\n");
         exit(-1);
        }

     	if ((nametx=(char **)malloc(ntxs*sizeof(char *))) ==NULL)
		{
       		puts("\n   Memory allocation error (7)\n");
       		exit(-1);
		}
        for(i=0;i<ntxs;i++)
     	if ((nametx[i]=(char *)malloc(MAXCAR*sizeof(char))) ==NULL)
		{
       		puts("\n   Memory allocation error (8)\n");
       		exit(-1);
		}

     	if ((targatx=(int*)malloc(ntxs*sizeof(int))) ==NULL)
       		{
       		puts("\n   Memory allocation error (9)\n");
       		exit(-1);
       		}
        targatxseconda=(int*)malloc(ntxs*sizeof(int));
    /*   	if ((count_tx=(int*)calloc(nclass, sizeof(int))) ==NULL)
       		{
       		puts("\n   Memory allocation error (10)\n");
       		exit(-1);
       		}*/


 if ((dist=(struct pattern*)malloc(ntrs*sizeof(struct pattern)))==NULL)
	{
	   puts("\n Memory allocation error (11) ");
	   exit(-1);
        }


     /* reads input data from data files */
	for(i=0;i<ntrs;i++)
           {
	     fscanf(fintrns,"%s",nametr[i]);
	     fscanf(fintrns,"%s",&classe[0]);
	     targatr[i]=daiclasse(classe[0]);
	     for(j=0;j<nfeat;j++)
               fscanf(fintrns,"%lf",&trnset[i*nfeat+j]);
	     //fscanf(fintrns,"%d",&targatr[i]);
	     //fscanf(fintrns,"%d",&seconda);
	     count_tr[targatr[i]-1]++;

          }

	for(i=0;i<ntxs;i++)
           {
	     fscanf(fintxs,"%s",nametx[i]);
	     fscanf(fintxs,"%s",&classe[0]);
	     targatx[i]=daiclasse(classe[0]);
	     targatxseconda[i]=daiclasse(classe[1]);
 	     for(j=0;j<nfeat;j++)
		fscanf(fintxs,"%lf",&texset[i*nfeat+j]);
	     //fscanf(fintxs,"%d",&targatx[i]);
	     //fscanf(fintxs,"%d",&targatxseconda[i]);
	     //count_tx[targatx[i]-1]++;
	   }

}


/*
   FILE_OPEN: reads input data from command line
*/

void file_open(char **argv)
{
   int h,c,i;
   char nomefile[20], numero[10];

   peso=atof(argv[1]);
   if ((fintrns= fopen(argv[2],"rb")) == NULL)
  	{
   	   printf("   File not found: '%s'\n",argv[1]);
   	   exit(-1);
  	}

   if ((fintxs= fopen(argv[3],"rb")) == NULL)
  	{
   	   printf("   File not found: '%s'\n",argv[2]);
   	   exit(-1);
  	}

   nclass=atoi(argv[4]);

   if (nclass >MAXCLASS)
	{
	   printf("Number of classes exceeded the maximum allowed %d\n",MAXCLASS);
	   exit(-1);
	}

   ntrs=atoi(argv[5]);

   ntxs=atoi(argv[6]);

   nfeat=atoi(argv[7]);

   Kmin=atoi(argv[8]);

   Kmax=atoi(argv[9]);
   if (Kmax >MAXK)
	{
	  printf("K parameter exceeded the maximum allowed %d\n",MAXK);
	  exit(-1);
	}
   if (Kmax >ntrs)
	{
	  printf("K is too large with respect to the number\n");
	  printf("of the training set samples\n");
	  exit(-1);
	}
   if ((Kmax-Kmin) > RANGE)  {
      printf("Range troppo grande per K");
      exit(-1);
   }
   

     /* ad ogni giro del ciclo eseguo le seguenti operazioni:
        - costruisco il nome di un file di output aggiungendo al prefisso 
          comune letto da prompt una cifra corrispondente ad uno dei valori
          di K all'interno del range;
        - apro per scrittura tale file e lo faccio puntare da un pointer
          appartenente al vettore fout.                                      */
   for (i=0;i<=(Kmax-Kmin);i+=2)  {
      strcpy(nomefile,argv[10]);
      itostr(numero,Kmin+i,2); 
      strcat(nomefile,numero);
      if ((fout[i/2]= fopen(nomefile,"wb")) == NULL)
  	{
   	  printf("   Can't open the output file : '%s'\n",nomefile);
   	  exit(-1);
 	}
   }

    /* si eseguono le stesse operazioni per aprire i files (un file per ogni k)
       su cui verranno memorizzate, per ogni pattern, le probabilita' a poste-
       riori delle varie classi */
   for (i=0;i<=(Kmax-Kmin);i+=2)  {
      strcpy(nomefile,argv[11]);
      itostr(numero,Kmin+i,2); 
      strcat(nomefile,numero);
      if ((fout2[i/2]= fopen(nomefile,"wb")) == NULL)
  	{
   	  printf("   Can't open the output file : '%s'\n",nomefile);
   	  exit(-1);
 	}
   }


   strcpy(nomeout,"RES");
   strcat (nomeout,argv[3]);
   if ((fres=fopen(nomeout,"a")) == NULL)
  	{
   	  printf("   Can't open the output file: '%s'\n",nomeout);
   	  exit(-1);
 	}

}

    
/*
   CALCDIST: calculates distances between a test pattern and all the 
	     training patterns
*/

void calcdist(int camp)     /* 'camp': test pattern to be classified  */ 
{
  double sp;
  int f,z;

     for(z=0;z<ntrs;z++)
	{
	  sp=0.0;                /* euclidean distance                */
	  for(f=0;f<nfeat;f += 2)
	     {
		sp+=QUAD(trnset[z*nfeat+f]-texset[camp*nfeat+f]);
	     }
	
	     sp *= peso;

	  for(f=1;f<nfeat;f += 2)
	     {
		sp+=QUAD(trnset[z*nfeat+f]-texset[camp*nfeat+f]);
	     }
	     	
	  dist[z].val=sqrt(sp);
	  dist[z].classe=targatr[z]-1;
	  dist[z].pos=z;
	}
    
}


/*
   CLASSIF: classify the test pattern 'camp'
*/
void classif(int camp, int K)
{
   int c,i,vic;
   int a,b;
   int tr;
   int cont[MAXCLASS],max_cont,tmp_rand;
   int ClassiConPiuVicini[MAXCLASS];
   int num_classi_vicine;
   int classe_assegnata;

   contarand=0;
   for(i=0;i<nclass;i++)
	cont[i]=0;

    
   for(vic=0;vic<K;vic++)
      cont[dist[vic].classe]++;
/*
   cont[c] is the number of training patterns
   belonging to the class 'c', among the K nearest neighborhoods
   of the test pattern 'camp'
   'camp' is assigned the label of the predominant class in the
   neighborhood. Ties are randomly broken.
*/
   max_cont = 0;
   for(i=0;i<nclass;i++)
	max_cont = MAX(max_cont,cont[i]);

/*
   If there is more than one class with the same maximum number
   of samples, the decision is made randomly.
*/
   num_classi_vicine = 0;
   for(i=0;i<nclass;i++)
      if(cont[i] == max_cont)
         ClassiConPiuVicini[num_classi_vicine++] = i+1;

   if(num_classi_vicine == 1)
       classe_assegnata = ClassiConPiuVicini[0];
   else
      {                             /* random decision */
      tmp_rand = rand() % num_classi_vicine;
      classe_assegnata = ClassiConPiuVicini[tmp_rand];
      contarand++;
      }
/*   {
   	classe_assegnata=0;
   	for(vic=0; ((vic<K)&&(!classe_assegnata)); vic++)
   		for(i=0; i<num_classi_vicine; i++)
   			if(dist[vic].class==ClassiConPiuVicini[i])
   			{
   				classe_assegnata=ClassiConPiuVicini[i];
   				break;
   			}
   }*/

   		
   		

   	

      
      fprintf(fout[(K-Kmin)/2],"%s          %d  ",nametx[camp],targatx[camp]);
      fprintf(fout[(K-Kmin)/2],"        %d        \n",classe_assegnata);
      fflush(fout[(K-Kmin)/2]);

      /* si scrivono su file le probabilita' a posteriori per le varie classi
         per il pattern in uso e per il valore di k attuale */
      fprintf(fout2[(K-Kmin)/2],"%s %d %d ",nametx[camp],targatx[camp]-1,targatxseconda[camp]-1);
      for (i=0;i<nclass;i++)
         fprintf(fout2[(K-Kmin)/2], "%4lf  ", (double) cont[i] / (double) K);
      fprintf(fout2[(K-Kmin)/2],"\n"); 

      /* si aggiornano i contatori relativi al valore di K attuale */
      if((classe_assegnata == targatx[camp])||(classe_assegnata == targatxseconda[camp]))
      {
           perclass[(K-Kmin)/2][classe_assegnata][classe_assegnata]++;
           count_tx[(K-Kmin)/2][classe_assegnata-1]++;
      }
      else
      {
           perclass[(K-Kmin)/2][targatx[camp]][classe_assegnata]++;
           conperc[(K-Kmin)/2]++;
           count_tx[(K-Kmin)/2][targatx[camp]-1]++;
      }		

           
}


/*
   INIT_RANDOM: initialize the random function
*/

void init_random()
{
   int iniz;
   time_t t;

   t=time(NULL);
   iniz=(unsigned int) t/2;
   srand(iniz);
}


/*
   QUICKSORT: call the recursive QSricors function
*/

void  quicksort(struct pattern *vett, int  grand)
{
   QSricors(vett, 0, grand-1);
}


/*
   QSricors: recursive fuction
*/

void  QSricors(struct pattern *vett, int  inf, int  sup)
{
   int i, j;
   double tmp_d;
   struct pattern tmp_s;

   i = inf;
   j = sup;
   tmp_d = vett[(inf + sup) / 2].val;
   do
   {
       while (vett[i].val < tmp_d  &&  i < sup)
	  i++;
       while (vett[j].val > tmp_d  &&  j > inf)
	  j--;
       if (i <= j)
       {
           tmp_s=vett[i];
	   vett[i] = vett[j];
	   vett[j] = tmp_s;
	   i++;
	   j--;
       }
   } while (i <= j);
   if (j > inf)  QSricors(vett, inf, j);
   if (i < sup)  QSricors(vett, i, sup);
}


void itostr(char *stringa, int num, int max_exp)
   /* stringa: conterra' la stringa di cifre;
      num:     il numero da convertire in stringa;
      max_exp: il numero totale di caratteri (si usano zeri all'inizio
	       per riempire il vuoto)*/

   {
      int i,n,exp;           /* exp contiene l'ordine di grandezza
			        di num */
      int cifra;             /* contiene di volta in volta la cifra */


      /* converte un numero (num) nella stringa (stringa) che lo visualizza */
      exp=1;
      n=num;
      while(n/=10) exp++;
      for(i=max_exp;i>exp;i--)
	 stringa[max_exp-i]='0';

      n=num;
	 for(i=exp;i>0;i--)
	   {
	     cifra=n/(int)(pow(10,i-1));
	     stringa[max_exp-i]='0'+cifra;
	     n-=cifra*(int)pow(10,i-1);
            }
          stringa[max_exp]='\0';
    }

