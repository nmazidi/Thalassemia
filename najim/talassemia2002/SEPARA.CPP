/****************************************************************************
*                                                                           *
*                   Separa ETICHETE DA outputA KNN da 12 nella              *
*                          forma <id > <classe> <predetta>  N M             *
*						           edit by G.Masala 25/03/2002                    *
*                                                                           *
****************************************************************************/
/* Nella riga di comando inserire:
	-> Nome del file di input classificato sa separare
   -> Nome del file originale
/***********************      Inizio Codice        *************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define nfeat 4

FILE *apri(char*,char*);
void leggi_esempio (FILE *in,int* id,int* classe,int* predetta);
//char dailabel(int i);
void calcolo(char *filename1,char *filename2);
char cerca(char *filename,int *id, float *feature, char *corretta);

int main(int argc, char **argv)
{
	char *filename1, *filename2;

   filename1=*++argv;
   filename2=*++argv;

	printf("\nAvvio il calcolo\n");

   calcolo(filename1,filename2);


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


void leggi_esempio (FILE *in,int* id,int* classe,int* predetta)
{
  	fscanf(in,"%d",id);
   fscanf(in,"%d",classe);
   fscanf(in,"%d",predetta);
}
 /*
char dailabel(int i)
{
	switch(i)
	{
		case 1 : return 'N';
		case 2 : return 'M';

	}
	return ' ';
}    */


void calcolo(char *filename1,char *filename2)
  {
   FILE *in,*outN,*outM;
   int id,classe,predetta,i,j;
   char corretta[3],corr;
   float *feature;

   in=apri(filename1,"r");


   outN=apri("Normali2.txt","w");
   outM=apri("Nonsani2.txt","w");

   feature=(float*)malloc(sizeof(float*)*nfeat);

   while(!feof(in))
	{
    if (!feof(in))
    {
    for (j=0;j<nfeat;j++)
    	feature[j]=0;
    leggi_esempio(in,&id,&classe,&predetta);
    if (predetta == 1)
    	{
       corr=cerca(filename2,&id,feature,&corretta[0]);
		 fprintf(outN,"%d %c ",id,corr);
       for (i=0;i<nfeat;i++)
       	fprintf(outN," %f ",feature[i]);
       fprintf(outN,"\n");
      }
      	else
          {
		 		corr=cerca(filename2,&id,feature,&corretta[0]);
		 		fprintf(outM,"%d %c ",id,corr);
       		for (i=0;i<nfeat;i++)
       			fprintf(outM," %f ",feature[i]);
       		fprintf(outM,"\n");
      	 }
    }
   }
   fclose(outN);
   fclose(outM);
   fclose(in);
}

char cerca(char *filename,int *id, float *feature, char *corretta)
{
	FILE *fp;
   int j,iden;
   char trovata;

   fp=apri(filename,"r");
   while(!feof(fp))
   	{
      fscanf(fp,"%d %s",&iden,corretta);
   	if (iden==*id)
      	{
         if (corretta[0]==NULL) printf("errore");
         trovata=corretta[0];
		   for (j=0;j<nfeat;j++)
   			fscanf(fp,"%f",&feature[j]);
         }
      }
   fclose(fp);
   return trovata;
}
