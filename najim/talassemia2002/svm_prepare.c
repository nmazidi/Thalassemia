#include <stdio.h>
#include <stdlib.h>

/* NELLA RIGA DI COMANDO INSERIRE:
	1) NUMERO ESEMPI
	2) NUMERO FEATURE
	3) CLASSE SELEZIONATA
	4) FILE DI INPUT
	4) FILE DI OUTPUT */

int main(int argc, char **argv)
{
	char *classel, *nomefileout, *nomefilein;
	char classe[10];
	int numesempi,numfeature;
	float valore;
	int nome;
	FILE *fp,*fw;
	
	int i,j;
	
	numesempi=atoi(*++argv);
	numfeature=atoi(*++argv);
	classel=*++argv;
	nomefilein=*++argv;
	nomefileout=*++argv;
	
	fp=fopen(nomefilein,"r");
	fw=fopen(nomefileout,"w");
	
	for(i=0; i<numesempi; i++)
	{
		fscanf(fp,"%d",&nome);
		fscanf(fp,"%s",&classe[0]);
		if(*classel==classe[0])
			fprintf(fw,"+1 ");
		else
			fprintf(fw,"-1 ");
			
		for(j=1; j<=numfeature; j++)
		{
			fscanf(fp,"%f",&valore);
			fprintf(fw,"%d:%.6f ",j,valore);
		}
		
		fprintf(fw,"\n");
	}
	
	fclose(fp);
	fclose(fw);
	
	return 0;
}
		
	