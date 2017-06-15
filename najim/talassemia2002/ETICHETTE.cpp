/****************************************************************************
*                                                                           *
*                   SCRIVI ETICHETE DA outputA KNN da 123 nella             *
*                          forma <id > <classe> <predetta>                  *
*						           edit by G.Masala 22/03/2002                    *
*                                                                           *
****************************************************************************/
/* Nella riga di comando inserire:
	-> Nome del file di input
/***********************      Inizio Codice        *************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ncl 3

FILE *apri(char*,char*);
void leggi_esempio (FILE *in,int* id,int* classe,int* predetta);
char dailabel(int i);
void calcolo(char *filename1);

int main(int argc, char **argv)
{
	char *filename1,*filename2;

   filename1=*++argv;


	printf("\nAvvio il calcolo\n");

   calcolo(filename1);


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

char dailabel(int i)
{
	switch(i)
	{
		case 0 : return 'N';
		case 1 : return 'M';
		case 2 : return 'M';
	}
	return ' ';
}


void calcolo(char *filename1)
  {
   FILE *in,*in2,*out;
   int id,classe,predetta;
   char classeL,predettaL;

   in=apri(filename1,"r");

   out=apri("cambiami.txt","w");



   while(!feof(in))
	{

    leggi_esempio(in,&id,&classe,&predetta);
    classeL=dailabel(classe);
    predettaL=dailabel(predetta);

    if (!feof(in))
    {
    fprintf(out,"%d %c %c\n",id,classeL,predettaL);
    }
   }
   fclose(out);
   fclose(in);
}


