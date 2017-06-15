/****************************************************************************
*                                                                           *
*                   Specializza set per  dati talassemia  nella             *
*                forma <id> <classe> <feature> da  N,A,B   a A/B            *
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
char cambia(char);
void calcolo(char*);


int main(int argc, char **argv)
{
	char *filename;

   filename=*++argv;
            
	printf("\nAvvio il calcolo\n");
   calcolo(filename);


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


void leggi_esempio (FILE *in, float *feature,int *id, char *esito)
{
   int i;

   fscanf(in,"%d",id);
   fscanf(in,"%s",esito);
   for (i=0;i<nparam;i++)
   	fscanf(in,"%f",&feature[i]);


   printf("id: %d classe: %d  \n",*id,*esito);
}

char cambia(char i)
{
	switch(i)
	{
		case 'A' : return 'A';
		case 'N' : return 'A';
		case 'B' : return 'B';
	}
   return 'D';
}

void calcolo(char *filename)
  {
   int *id,d,h;
   char esitoL;
   char esitop[3];
   FILE *out,*in;
   float *feature;

   in=apri(filename,"r");
   out=apri("fileTH.txt","w");
   feature=(float*)malloc(sizeof(float*)*nparam);


   id=&d;


   while(!feof(in))
	{
    leggi_esempio (in,feature,id,esitop);
    esitoL=cambia(esitop[0]);

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


