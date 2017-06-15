/****************************************************************************
*                                                                           *
*                  Copia file di 4 feature così come è                      *
*                                                          *
*						  edit by G.Masala 29/04/2002                             *
*                                                                           *
****************************************************************************/
/* Nella riga di comando inserire:
	-> Nome del file di input
/***********************      Inizio Codice        *************************/

#include <stdio.h>


FILE *apri(char*,char*);
void calcolo(char *filename1);

int main(int argc, char **argv)
{
	char *filename1;

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
	
	}

	return fp;
}



void calcolo(char *filename1)
  {
   FILE *in,*out;
   int respon,i;
   float feature[4];

   in=apri(filename1,"r");
   out=apri("cambiami.txt","w");

   while(!feof(in))
	{
    fscanf(in,"%d",&respon);
    fprintf(out,"%d",&respon);
    for(i=0;i<4;i++)
    	  {
        fscanf(in,"%f",&feature[i]);
        fprintf(out,"%f",&feature[i]);
        }

   }
   fclose(out);
   fclose(in);
}


