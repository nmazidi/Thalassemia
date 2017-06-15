/****************************************************************************
*                                                                           *
*                   Converti dati talassemia  nella                         *
*                forma <id> <classe> <feature> con 0,1,2                    *
*						    edit by G.Masala 5/03/2002                            *
*                                                                           *
****************************************************************************/
/* Nella riga di comando inserire:
	-> Nome del file di input
/***********************      Inizio Codice        *************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define nparam 4

FILE *apri(char*,char*);   
void leggi_esempio (FILE *in, float *feature,int *id, int *esito);
char cambia(int);
void calcolo(char*);


int main(int argc, char **argv)
{
	char *filename;

   filename=*++argv;

	printf("\nAvvio il calcolo\n");

   calcolo(filename);

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


void leggi_esempio (FILE *in, float *feature,int *id, int *esito)
{
   int i;

   fscanf(in,"%d",id);
   fscanf(in,"%d",esito);
   for (i=0;i<nparam;i++)
   	fscanf(in,"%f",&feature[i]);


   printf("id: %d classe: %d  \n",*id,*esito);
}

char cambia(int i)
{
	switch(i)
	{
		case 1 : return '0';
		case 2 : return '2';
		case 3 : return '1';
		case 4 : return '1';
		case 0 : return '0';
      case 5 : return '1';
	}
   return 8;
}

void calcolo(char *filename)
  {
   int *id,d,h,*esito,esit;
   char esitoL;
   FILE *out,*in;
   float *feature;

   in=apri(filename,"r");
   out=apri("fileTH.txt","w");
   feature=(float*)malloc(sizeof(float*)*nparam);
   id=&d;
   esito=&esit;
   while(!feof(in))
	{
    leggi_esempio (in,feature,id,esito);
    esitoL=cambia(*esito);

    if (!feof(in))
    {
    fprintf(out,"%d ",*id);
    fprintf(out,"%c ",esitoL);
    for(h=0; h<nparam; h++)
        fprintf(out," %f",feature[h]);
    fprintf(out,"\n");
    }
   }
   fclose(out);
   fclose(in);
}


