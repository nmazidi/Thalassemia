#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//versione per la discriminazione di due sole classi N/M per talassemia G. Masala
/* Nella riga di comando inserire:
	-> Nome del file di input
	-> Nome del file di output
	-> Soglia di reiezione */


/* Il file di input deve avere:
	1) Numero di classi
	2) Stringa delle classi (LRWAT)
	3) Numero di esempi
	4) Elenco dei files da dove prelevare i dati nello stesso ordine della stringa classi
	5) Nome del file con i target */


void stampaConfusione(FILE *file, int **Tbl, char* stringaClassi,int nT);

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


char **leggiInput(char* nomefile,int *ncl,char** stringaClassi,int *nes)
{
	int i;
	FILE *fp;
	char **nomi;
	char prova[50];

	*stringaClassi=(char*)malloc(sizeof(char)*50);
	fp=apri(nomefile,"r");
	fscanf(fp,"%d %s %d",ncl,*stringaClassi,nes);

	printf("\nNumero classi: %d\nStringa classi: %s\nNumero esempi: %d",*ncl,*stringaClassi,*nes);
	nomi=(char**)malloc(sizeof(char*)*150);
	for(i=0; i<(*ncl); i++)
	{
		nomi[i]=(char*)malloc(sizeof(char)*200);
		fscanf(fp,"%s",&nomi[i][0]);
		printf("\n%s",nomi[i]);
	}
	nomi[i]=(char*)malloc(sizeof(char)*150);
	fscanf(fp,"%s",&nomi[i][0]);
	printf("\n%s\n",nomi[*ncl]);
 	fclose(fp);
	return nomi;
}


FILE **apriFiles(char **nomi,int n)
{
	int i;
	FILE **fp;

	printf("\nApertura di %d files.\n",n);
	fp=(FILE**)malloc(sizeof(FILE*)*n);

	for(i=0; i<n; i++)
	{
		printf("Tentativo su: %s.\n",nomi[i]);
		fp[i]=apri(nomi[i],"r");
	}


	return fp;
}

void azzera(float *vettore,int dim)
{
	int i;
	for(i=0; i<dim; i++) vettore[i]=0.0;
}


float* inizializza(int dim)
{
	float *vettore;
	vettore=(float*)malloc(sizeof(float)*dim);
	azzera(vettore,dim);
	return vettore;
}

void classifica(int **matrice,float *output,int ncl,int prima,int seconda, float RJTThr)
{
	int i,j,max;
	float min;
	
	max=2;
	if(output[0]>0) max=1;
		else max=2;
		
/*	min=1000.;
	for(i=0; i<ncl; i++)
		if(i!=max)
			if((output[max]-output[i])<min)
				min=output[max]-output[i]; */
			
/*	if(fabs(output[max])<RJTThr)
		matrice[prima][ncl]++;
	else*/
		if(max==prima)
			matrice[max][max]++;
		else
			matrice[prima][max]++;
}		
	



int traduci(char classe, char* stringaClassi, int ncl)
{
	int i;
	
	for(i=0; (i<ncl) && (classe!=stringaClassi[i]); i++);
	
	return (i==ncl) ? -1 : i;
}
		


void leggiTarget(FILE *fp,int *prima, int *seconda,char *stringaClassi,int ncl)
{
	char classe[10];
	
	fscanf(fp,"%s",&classe);
	(*prima)=traduci(classe[0],stringaClassi,ncl);
	(*seconda)=traduci(classe[1],stringaClassi,ncl);
}

		
void leggiECalcola(char* fileout, FILE **fp, int ncl,int nes ,float RJTThr,char *stringaClassi)
{
	int i,j,k,cls;
	float *output,val;
	int **matrice;
	char nome[10];
	int prima,seconda;
	FILE *out;
	
	/*INIZIALIZZAZIONE DELLA MATRICE DI CONFUSIONE*/
	matrice=(int**)malloc(sizeof(int*)*ncl);
	for(i=0; i<=ncl; i++)
	{
		matrice[i]=(int*)malloc(sizeof(int)*(ncl+1));
		for(j=0; j<=ncl; j++)
			matrice[i][j]=0;
	}
	
	output=(float*)malloc(sizeof(float)*ncl);
	for(i=0; i<nes; i++)
	{
		//printf("%d ",i+1);
		for(j=0; j<=ncl; j++)
		{
			fscanf(fp[j],"%f",&output[j]);
			//printf("%.6f ",output[j]);
		}
		//printf("\n");
		leggiTarget(fp[j],&prima,&seconda,stringaClassi,ncl);
		//printf("%d %d\n",prima,seconda);
		classifica(matrice,output,ncl,prima,seconda,RJTThr);
	}
	
	out=apri(fileout,"w");
	printf("Stampo la matrice di confusione su %s.\n",fileout);
	stampaConfusione(out,matrice,stringaClassi,ncl);
	printf("\nStampa effettuata.\n");
	fclose(out);
	
	
	for(i=0; i<ncl; i++) free(matrice[i]);
	free(output);
}

			
void chiudiFiles(char **nomefiles,FILE **fp,int n)
{
	int i;
	
	for(i=0; i<n; i++)
	{
		free(nomefiles[i]);
		fclose(fp[i]);
	}
}				
	
	
		
int main(int argc, char **argv)
{
	int n,ncl,nes;
	float RJTThr;
	char **nomefiles, *fileout, *stringaClassi;
	FILE **fp;	

	
	nomefiles=leggiInput(*++argv,&ncl,&stringaClassi,&nes);
	fp=apriFiles(nomefiles,ncl+1);
	
	fileout=*++argv;
	RJTThr=atof(*++argv);	
	printf("\nAvvio il calcolo\n");
	leggiECalcola(fileout,fp,ncl,nes,RJTThr,stringaClassi);
		
	printf("Chiudo i files.\n");
	chiudiFiles(nomefiles,fp,ncl+1);
	
	free(fp);
	free(nomefiles); 		
	return 0;
}
	
	
void stampaConfusione(FILE *file, int **Tbl, char* stringaClassi,int nT)
{
  register int i,j;
  unsigned int totOK=0,totRJT=0,tot=0;
  unsigned int ni[10];


  for(i=0;i<=nT;i++)
    fprintf(file," %6c",stringaClassi[i]);


  fprintf(file,"      OK   BAD  RJT  TOT  ACC\n");

  for(i=0;i<nT+6;i++)
    fprintf(file,"------");
  fprintf(file,"-");

  for(i=0;i<nT;i++) {
    for(j=0,ni[i]=0;j<nT;j++)
      if(i!=j) ni[i] += Tbl[i][j];

    totOK += Tbl[i][i];
    totRJT += Tbl[i][nT];
    tot += Tbl[i][i]+ni[i]+Tbl[i][nT];
  }

  for(i=0;i<nT;i++) {
    fprintf(file,"\n %c |",stringaClassi[i]);

    for(j=0;j<nT;j++) {
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
  for(j=0;j<=nT;j++)
    fprintf(file,"       ");
  fprintf(file," %4d %4d %4d %4d %6.2f%%",
	  totOK,tot-totOK,totRJT,tot,
	  ((float)totOK/((float)tot)*100));



  fprintf(file,"\n\n\n");
  fprintf(file,"  Accuracy    : %5.2f%%\n",((float)totOK/(float)tot)*100.);
  fprintf(file,"  Uncertainty : %5.2f%%\n",((float)totRJT/((float)(tot+totRJT)))*100.);
  fprintf(file,"\n");
}
