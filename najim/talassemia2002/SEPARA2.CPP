/****************************************************************************
*                                                                           *
*                   Separa ETICHETE DA outputA KNN da 12 nella              *
*                          forma <id > <classe> <predetta>  NM              *
*						           edit by G.Masala 25/03/2002                    *
*                                                                           *
****************************************************************************/
/* Nella riga di comando inserire:
	-> Nome del file di input
/***********************      Inizio Codice        *************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define nfeat 4    

FILE *apri(char*,char*);
void leggi_esempio (FILE *in,int* id,int* classe,int* predetta);
//char dailabel(int i);
void calcolo(char *filename1,char *filename2);
char cerca(FILE *filename,int *id, float *feature, char *corretta);

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
   FILE *in,*fp,*outN,*outM;
   int id,iden,classe,predetta,i,j;
   char corretta[3];
   float *feature;

   in=apri(filename1,"r");

   fp=apri(filename2,"r");
   outN=apri("Normali.txt","w");
   outM=apri("Nonsani.txt","w");

   feature=(float*)malloc(sizeof(float*)*nfeat);

   while(!feof(fp))
	{
    if (!feof(fp))
    {
    for (j=0;j<nfeat;j++)
    	feature[j]=0;
    fscanf(fp,"%d %s",&iden,corretta);
	 for (j=0;j<nfeat;j++)
   	  fscanf(fp,"%f",&feature[j]);
    rewind(in);
    while (!feof(in))
    	{

      leggi_esempio(in,&id,&classe,&predetta);
    	if ((predetta == 1)&&(id==iden))
    	{
       if (!feof(in))
       {
       fprintf(outN,"%d %c ",id,corretta[0]);
       for (i=0;i<nfeat;i++)
       	fprintf(outN," %f ",feature[i]);
       fprintf(outN,"\n");
       break;
       }
      }
      else if ((predetta != 1)&&(id==iden))
          {
           if (!feof(in))
          {
          fprintf(outM,"%d %c ",id,corretta[0]);
       	 for (i=0;i<nfeat;i++)
       			fprintf(outM," %f ",feature[i]);
       	 fprintf(outM,"\n");
          break;
          }
      	 }
       }
       
   }
   }
   fclose(outN);
   fclose(outM);
   fclose(in);
   fclose(fp);
}

