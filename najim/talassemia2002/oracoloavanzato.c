#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* NELLA RIGA DI COMANDO INSERIRE IL NOME DEL FILE CONTENENTE LE INFO:
1) Numero classificatori
2) Numero classi
3) Numero pattern
4) Nomi dei files da cui prelevare i dati
*/


typedef struct feature
{
	char nome[10];
	//float **output;
	int *cls,t1,t2;
	int *azzeccato;
} FEATURE;

typedef struct statistiche
{
	float *media,*devst;
} STATISTICHE;

int fattoriale(int n)
{
	int i;
	unsigned fatt=1.0;
	
	for(i=1; i<=n; i++)
		fatt *= i;
		
	return fatt;
}

int *inizializzaInt(int init,int dim)
{
	int i;
	int* vettore;
	
	vettore=(int*)malloc(sizeof(int)*dim);
	for(i=0; i<dim; i++) vettore[i]=init;
	
	return vettore;
}

float* inizializzaFloat(float init,int dim)
{
	int i;
	float *vettore;
	vettore=(float*)malloc(sizeof(float)*dim);
	for(i=0; i<dim; i++) vettore[i]=init;
	return vettore;
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




void scriviPattern(int gruppo,char *nomePattern)
{
	char nomefile[10];
	FILE *fp;
	
	sprintf(nomefile,"%d.cls",gruppo);
	fp=fopen(nomefile,"a");
	fprintf(fp,"%s\n",nomePattern);
	fclose(fp);
}

FEATURE *allocaFeatures(int classificatori,int classi,int pattern)
{
	int i,j;
	FEATURE *features;
	
	features=(FEATURE*)malloc(sizeof(FEATURE)*pattern);
	
	for(i=0; i<pattern; i++)
	{
		features[i].cls=inizializzaInt(-1,classificatori);
		features[i].azzeccato=inizializzaInt(0,classificatori);
		/*features[i].output=(float**)malloc(sizeof(float*)*classificatori);
		for(j=0; j<classificatori; j++)
			features[i].output[j]=(float*)malloc(sizeof(float)*classi);*/
	}
	
	return features;
}

int leggiFeature(FILE *fp,int ncl,int classificatore,FEATURE *features)
{
	int i,cls;
	//float valore;
	
	fscanf(fp,"%s %d %d %d",&(features->nome[0]),&(features->t1),&(features->t2),&cls);
	/*for(i=0; i<ncl; i++)
	{
		fscanf(fp,"%f",&valore);
		features->output[classificatore][i]=100.*valore;
	}*/

	return cls;
		
}


void leggiEsempi(char* nomefile,int classi,int pattern,int classificatore,FEATURE* features)
{
	int i;
	FILE *fp;
	
	fp=apri(nomefile,"r");
	
	for(i=0; i<pattern; i++)
		features[i].cls[classificatore]=leggiFeature(fp,classi,classificatore,&features[i]);
		
	fclose(fp);
}
	
		

FEATURE* leggiFile(char* nomefile,int* classificatori,int* classi, int *pattern)
{
	int i;
	FEATURE *features;
	char file[50];
	FILE *fp;
	
	fp=apri(nomefile,"r");
	fscanf(fp,"%d %d %d",classificatori,classi,pattern);
	
	features=allocaFeatures(*classificatori,*classi,*pattern);
	
	for(i=0; i<(*classificatori); i++)
	{
		fscanf(fp,"%s",&file[0]);
		leggiEsempi(file,*classi,*pattern,i,features);
	}
	
	fclose(fp);
	
	return features;
}

int classifica(float *out,int ncl)
{
	int i,maxi;
	
	maxi=0;
	for(i=1; i<ncl; i++)
		if(out[i]>out[maxi]) maxi=i;
		
	return maxi;
}	

void classificaFeatures(FEATURE* features,int classificatori,int classi,int pattern)
{
	int i,j;
	
	for(i=0; i<pattern; i++)
		for(j=0; j<classificatori; j++)
		{
			//features[i].cls[j]=classifica(features[i].output[j],classi);
			if((features[i].cls[j]==features[i].t1)||(features[i].cls[j]==features[i].t2))
				features[i].azzeccato[j]=1;
		}
}

/*STATISTICHE *calcolaStatistiche(FEATURE* features,int classificatori,int classi,int pattern)
{
	int i,j;
	float scarto;
	STATISTICHE *statistica;
	
	statistica=(STATISTICHE*)malloc(sizeof(STATISTICHE));
	statistica->media=inizializzaFloat(0.0,classificatori);
	statistica->devst=inizializzaFloat(0.0,classificatori);
	
	for(j=0; j<classificatori; j++)
	{
		for(i=0; i<pattern; i++)
			statistica->media[j] += (features[i].output[j][features[i].cls[j]]);
			
		statistica->media[j] /= ((float)pattern);
	}
	
	for(j=0; j<classificatori; j++)
	{
		for(i=0; i<pattern; i++)
		{
			scarto = ((features[i].output[j][features[i].cls[j]])-(statistica->media[j]));
			statistica->devst[j] += scarto*scarto;
		}
               		
		statistica->devst[j] /= (float)pattern;
		statistica->devst[j] = sqrt(statistica->devst[j]);
	}
	
	return statistica;
}*/

int calcolaCombinazioni(int n)
{
	int i, totali,fattn;
	
	
	totali=0;
	
	fattn=fattoriale(n);
	for(i=1; i<=n; i++)
		totali += fattn/(fattoriale(i)*fattoriale(n-i));
		
	return totali;
}

int converti(FEATURE *features,int classificatori,int *cls)
{
	int i;
	int gruppo;
	
	gruppo=0;
	for(i=0; i<classificatori; i++)
		if(features->azzeccato[i])
		{
			gruppo += pow(2,i);
			*cls=features->cls[i];
		}
		
	
	return gruppo;
}
		

void scriviContributi(int **contributi,int totali,int classi,int *totpattern,int pattern)
{
	char nomefile[10];
	int i,j;
	int acc,tot,toti;
	int* perclasse;
	FILE *fp;
	
	
	perclasse=inizializzaInt(0,classi);
	for(i=0; i<totali; i++)
	{
		sprintf(nomefile,"%d.cls",i);
		fp=apri(nomefile,"a");
		fprintf(fp,"\nContributo del gruppo %d\n",i);
		toti=0;
		for(j=0; j<classi; j++)
		{
			fprintf(fp,"%.2f\n",100.*((float)contributi[i][j])/((float)totpattern[j]));
			perclasse[j] += contributi[i][j];
			toti +=contributi[i][j];
		}
		fprintf(fp,"\nTotale: %.2f %%\n",100.*((float)toti)/((float)pattern));
		fclose(fp);
	}
	
	printf("\nContributo di tutti i classificatori\n");
	acc=0; tot=0;
	for(j=0; j<classi; j++)
	{
		printf("Classe %d : %.2f %%\n",j,100.*((float)perclasse[j])/((float)totpattern[j]));
		acc += perclasse[j];
		tot += totpattern[j];
	}
	
	printf("\nAccuratezza complessiva: %.2f\n",100.*((float)acc)/((float)tot));

	free(perclasse);
}
		
		
			
			

void calcolaContributi(FEATURE *features,int classificatori,int classi,int pattern)
{
	int i,cls,gruppo;
	int **contributi,*totpattern;
	int totali;
	
	totali=calcolaCombinazioni(classificatori);

	contributi=(int**)malloc(sizeof(int)*totali);
	for(i=0; i<totali; i++)
		contributi[i]=inizializzaInt(0,classi);
		
	totpattern=inizializzaInt(0,classi);
	for(i=0; i<pattern; i++)
	{
		gruppo=converti(&features[i],classificatori,&cls);
		if(gruppo)
		{
			scriviPattern(gruppo-1,features[i].nome);		
			contributi[gruppo-1][cls]++;
			totpattern[cls]++;
		}
		else
			totpattern[features[i].t1]++;
	
	}
	
	scriviContributi(contributi,totali,classi,totpattern,pattern);
	
	for(i=0; i<totali; i++)
		free(contributi[i]);
	free(contributi);
	free(totpattern);
	
}

void scriviStatistiche(STATISTICHE *md,int cl)
{
	int i;
	FILE *fp;
	
	fp=fopen("statistiche.cls","w");
	fprintf(fp,"\nStatistiche sui %d classificatori:\n",cl);
	for(i=0; i<cl; i++)
	{
		fprintf(fp,"\nClassificatore %d.\n",i);
		fprintf(fp,"	Media: %.6f\n	Deviazione: %.6f\n",md->media[i],md->devst[i]);
	}
	fclose(fp);
}
	
void deallocaFeature(FEATURE* features,int pattern,int classificatori)
{
	int i,j;
	
	for(i=0; i<pattern; i++)
	{
		free(features[i].azzeccato);
		free(features[i].cls);
	/*	for(j=0; j<classificatori; j++)
			free(features[i].output[j]);
		free(features[i].output);*/
	}
}

void deallocaStatistica(STATISTICHE* st)
{
	free(st->media);
	free(st->devst);
}

int main(int argc,char **argv)
{
	int i;
	FEATURE *features;
	int classificatori,classi,pattern;
	//STATISTICHE *mediadvst;
	
	features=leggiFile(*++argv,&classificatori,&classi,&pattern);
	classificaFeatures(features,classificatori,classi,pattern);
	//mediadvst=calcolaStatistiche(features,classificatori,classi,pattern);
	calcolaContributi(features,classificatori,classi,pattern);
	//scriviStatistiche(mediadvst,classificatori);
	
	deallocaFeature(features,pattern,classificatori);
	free(features);
	//deallocaStatistica(mediadvst);
	//free(mediadvst);
	
	return 0;
}
	
	
	


	