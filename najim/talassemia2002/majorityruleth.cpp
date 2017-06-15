/****************************************************************************
*                                                                           *
*                     Majority rule  per file nella forma                   *
*                     <id> <cls> <num 1>    con ordine NAB                  *
*						    edit by G.Masala 22/03/2002                            *
*                                                                           *
****************************************************************************/
/* Nella riga di comando inserire:
	-> Nome del file di input


  Il file di input deve avere:
	1) Numero di classi
   2) Numero di classificatori (se diverso da 3 fare alcune modifiche)
   3) Numero di esempi 
	4) Elenco dei file dei classificatori da valutare (il primo classificatore
      deve essere il più affidabile)


/***********************      Inizio Codice        *************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE *apri(char* ,char*);
char **leggiInput(char*,int*,int*,int*);
void stampaConfusione(FILE*,int**,char*,int);
void leggiEsempio(FILE* fp, int *id,int *clas1,int *cls);
void classifica(int **matrice, int classe,int prima);
void leggiECalcola(char**,int,int,int );
int scegliClasse(int**,int,int,int);
void stampaConfusione(FILE*,int**,char*,int);

int main(int argc, char **argv)
{
	int ncl,nes,numclassif;
	char **nomefiles,*filename;

   filename=*++argv;


	nomefiles=leggiInput(filename,&ncl,&numclassif,&nes);
	printf("\nAvvio il calcolo\n");

	leggiECalcola(nomefiles,ncl,numclassif,nes);

	free(nomefiles);
	return 0;
}

FILE *apri(char* nomefile,char* modo)
{
	FILE *fp;

	fp=fopen(nomefile,modo);
	if(fp==NULL)
	{
		printf("\nErrore di lettura nel file: %s\n",nomefile);
		exit(0);
	}

	return fp;
}


char **leggiInput(char* nomefile,int *ncl,int *nclassif,int *nes)
{
	int i;
	FILE *fp;
	char **nomi;

	fp=apri(nomefile,"r");
	fscanf(fp,"%d %d %d ",ncl,nclassif,nes);

	printf("\nNumero classi: %d\nNumero dei classificatori: %d\nNumero esempi: %d\n",*ncl,*nclassif,*nes);
	nomi=(char**)malloc(sizeof(char*)*50);
	for(i=0; i<*nclassif; i++)
	{
		nomi[i]=(char*)malloc(sizeof(char)*50);
		fscanf(fp,"%s",&nomi[i][0]);
		printf("\n%s",nomi[i]);
	}
 	fclose(fp);
	return nomi;
}

void leggiEsempio(FILE* fp, int *id,int *clas1,int *cls)
{

	fscanf(fp,"%d",id);
   fscanf(fp,"%d",clas1);
	fscanf(fp,"%d",cls);


}

void classifica(int **matrice, int classe,int prima)
{
		if(classe==prima)
			matrice[classe][classe]++;
		else
			matrice[prima][classe]++;
}

void leggiECalcola(char **nomi, int ncl, int nclassif, int nes)
{
	int i,j,id,clas1,cls,classi;
	FILE *outA,*outB,*in;
   int **memorizza,**matrice;
   

   /*INIZIALIZZAZIONE MATRICE DI CONFUSIONE*/
   matrice=(int**)malloc(sizeof(int*)*ncl);
   for(i=1; i<=ncl; i++)
	{
		matrice[i]=(int*)malloc(sizeof(int)*(ncl+1));
		for(j=1; j<=ncl; j++)
			matrice[i][j]=0;
	}
   /*INIZIALIZZAZIONE MATRICE DEI DATI IN MEMORIA*/
   memorizza=(int**)malloc(sizeof(int*)*(nes));
   for(i=0; i<(nes);i++)
   	{
      memorizza[i]=(int*)malloc(sizeof(int)*(3+nclassif));
      for(j=0;j<(nclassif+3);j++)
      	memorizza[i][j]=0;
      }
   /*memorizzo tutti i dati in una matrice*/
	for(j=0; j<(nclassif); j++)
	{
      in= apri(nomi[j],"r");
      for(i=0; i<nes; i++)
      	{
			leggiEsempio(in,&id,&clas1,&cls);
         memorizza[i][0]=id;
         memorizza[i][1]=clas1;
         memorizza[i][2]=8;
         memorizza[i][3+j]=cls;
         }
      fclose(in);
   }

   /*apro il file di output calcolo e stampo l'esito*/
	outA=apri("Dettagli.txt","w");
   fprintf(outA,"id  cls c1 c2 c3 esito\n");
   for(i=0; i<nes; i++)
      	{
         classi=scegliClasse(memorizza,nclassif,i,ncl);
         fprintf(outA,"%d  %d   %d  %d  %d   %d\n",memorizza[i][0],memorizza[i][1],
         memorizza[i][3],memorizza[i][4],memorizza[i][5],classi);
         classifica(matrice,classi,memorizza[i][1]);
         }
   printf("\nStampa file con i dettagli effettuata.\n");
	fclose(outA);

   outB=apri("Risultati_major.txt","w");
	printf("Stampo la matrice di confusione su Risultati_major.txt\n");
	stampaConfusione(outB,matrice,"NAB",ncl);
	printf("\nStampa effettuata.\n");
	fclose(outB);
}

int scegliClasse(int **memorizza,int numclassif,int i,int ncl)
{
	int k,t,max,tutti_diversi,classe;
   int risultati[5];

   max=0;
   tutti_diversi=0;
   for (k=1;k<=ncl;k++)
       risultati[k]=0;

   risultati[memorizza[i][3]]++;

   for(k=1;k<numclassif;k++)
      risultati[memorizza[i][3+k]]++;

   for(t=1;t<=ncl;t++)
      if (risultati[t]>max)
      		{
            max=risultati[t];
            classe=t;
            }

   /*il controllo di seguito è valido per tre classificatori, se capita che sono tutti discordi scelgo
   il primo classificatore che deve essere il più potente  */

   if  ((memorizza[i][3]!=memorizza[i][4])&&(memorizza[i][4]!=memorizza[i][5])&&(memorizza[i][3]!=memorizza[i][5]))
        tutti_diversi=1;

   if (tutti_diversi!=0) return memorizza[i][3];
                  else   return classe;

}


void stampaConfusione(FILE *file, int **Tbl, char* stringaClassi,int nT)
{
  register int i,j;
  unsigned int totOK=0,totRJT=0,tot=0;
  unsigned int ni[10];


  for(i=0;i<nT;i++)
    fprintf(file," %6c",stringaClassi[i]);


  fprintf(file,"      OK   BAD  RJT  TOT  ACC\n");

  for(i=0;i<nT+6;i++)
    fprintf(file,"------");
  fprintf(file,"-");

  for(i=1;i<=nT;i++) {
    for(j=1,ni[i]=0;j<=nT;j++)
      if(i!=j) ni[i] += Tbl[i][j];

    totOK += Tbl[i][i];
    totRJT += Tbl[i][nT];
    tot += Tbl[i][i]+ni[i]+Tbl[i][nT];
  }
  /**/
  for(i=1;i<=nT;i++) {
    fprintf(file,"\n %c |",stringaClassi[i]);

    for(j=1;j<=nT;j++) {
      fprintf(file," %6.2f",(((float)Tbl[i][j])/((float)(Tbl[i][i]+ni[i]+Tbl[i][nT])))*100.);
    }
    if(ni[i]+Tbl[i][i]>0)
      fprintf(file," %4d %4d %4d %4d %6.2f%%",
	    Tbl[i][i],
       ni[i],
       Tbl[i][nT],
        ni[i]+Tbl[i][i],
	(((float)Tbl[i][i])/((float)(ni[i]+Tbl[i][i])))*100.);
    else
      fprintf(file," %4d %4d %4d %4d   -.-%%",
	    Tbl[i][i],
       ni[i],
       Tbl[i][nT],
        ni[i]+Tbl[i][i]);
  }

  fprintf(file,"\n   |");

  if(tot-totRJT) tot -= totRJT;
  for(j=0;j<nT;j++)
    fprintf(file,"       ");
  fprintf(file," %4d %4d %4d %4d %6.2f%%",
	  totOK,tot-totOK,totRJT,tot,
	  ((float)totOK/((float)tot)*100));



  fprintf(file,"\n\n\n");
  fprintf(file,"  Accuracy    : %5.2f%%\n",((float)totOK/(float)tot)*100.);
  fprintf(file,"  Uncertainty : %5.2f%%\n",((float)totRJT/((float)(tot+totRJT)))*100.);
  fprintf(file,"\n");
}







