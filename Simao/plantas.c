/*****************************************************************/
/*          Biblioteca plantas | PROG2 | MIEEC | 2020/21         */
/*****************************************************************/

#include "plantas.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

planta *planta_nova(const char *ID, const char *nome_cientifico, char **alcunhas, int n_alcunhas, int n_sementes)
{
	int cont;

	planta *nplanta;
	nplanta = malloc(sizeof(planta));
	
	if(alcunhas==NULL)
	{
		nplanta->alcunhas = NULL;
		nplanta->n_alcunhas = 0;
	}

	else
	{
		nplanta->alcunhas = malloc(n_alcunhas*sizeof(char*));
		for(cont=0;cont<n_alcunhas;cont++)
		{
			nplanta->alcunhas[cont]=malloc((strlen(alcunhas[cont])+1)*sizeof(char));
			strcpy(nplanta->alcunhas[cont],alcunhas[cont]);
		}
		nplanta->n_alcunhas = n_alcunhas;
	}
	
	strcpy(nplanta->nome_cientifico, nome_cientifico);
	strcpy(nplanta->ID, ID);
	
	nplanta->n_sementes = n_sementes;

	return nplanta;
}

colecao *colecao_nova(const char *tipo_ordem)
{
	if(strcmp(tipo_ordem,"id")!=0 && strcmp(tipo_ordem,"nome")!=0)
		return NULL;

	colecao *ncolecao = malloc(sizeof(colecao));
	ncolecao->plantas=NULL;
	ncolecao->tamanho=0;
	strcpy(ncolecao->tipo_ordem,tipo_ordem);

	return ncolecao;
}
int planta_insere(colecao *c, planta *p)
{
	planta *nova;
	int i, j, k, flag1=0, flag2=0;

	if(c==NULL || p==NULL)
		return -1;

	for(i=0;i<c->tamanho; i++){
		if(strcmp(p->ID, c->plantas[i]->ID)==0){
			nova=c->plantas[i];
			nova->n_sementes = nova->n_sementes + p->n_sementes;
			flag2=1;
			for(k=0;k<p->n_alcunhas;k++){
				flag1=0;
				for(j=0;j<nova->n_alcunhas;j++){
					if(strcmp(p->alcunhas[k], nova->alcunhas[j])==0){
						flag1=1;
						break;
					}

				}
				if(flag1==0){
					nova->n_alcunhas++;
					nova->alcunhas=realloc(nova->alcunhas,nova->n_alcunhas*sizeof(char*));
					nova->alcunhas[nova->n_alcunhas-1]=malloc((strlen(p->alcunhas[k])+1)*sizeof(char));
					strcpy(nova->alcunhas[nova->n_alcunhas-1],p->alcunhas[k]);
				}
			}	
				
		}

	}
	if(flag2==1)
		return 1;

	if(c->tamanho==0)
		c->plantas=malloc(sizeof (planta*));
	
	else
		c->plantas=realloc(c->plantas,(c->tamanho+1)*sizeof(planta*));
	
	c->tamanho++;
	c->plantas[c->tamanho-1]=p;

	if(strcmp(c->tipo_ordem,"nome")==0){
		strcpy(c->tipo_ordem, "id");
		colecao_reordena(c, "nome");
	}
		
	
	if(strcmp(c->tipo_ordem,"id")==0){
		strcpy(c->tipo_ordem, "nome");
		colecao_reordena(c, "id");
	
	}
		
	return 0;

}

int colecao_tamanho(colecao *c)
{
	if(c->tamanho <= 0)
		return -1;

	else
		return c->tamanho;
}

colecao *colecao_importa(const char *nome_ficheiro, const char *tipo_ordem)
{
	colecao *c;
	planta *p;
	int cont=0,i=0;
	int j,ns,na;
	char str[512],id[10],nc[MAX_NAME],*token,str1[512];
	FILE *f;
	if(nome_ficheiro == NULL || tipo_ordem == NULL)
		return NULL;
	c = colecao_nova(tipo_ordem);
	if(c == NULL)
		return NULL;
	
	char **al; 

	f=fopen(nome_ficheiro,"r");
	while(fgets(str1,512,f) != NULL)
	{
		i=0;
		al = NULL;
		token = strtok(str1,",");
		strcpy(id,token);
		token = strtok(NULL,",");
		strcpy(nc,token);
		token = strtok(NULL,",");
		ns = atoi(token);
		token = strtok(NULL,",");
		while(token != NULL)
		{
			if(i!=0)
				al = realloc(al, sizeof(char *) * (i+1));

			else
				al = malloc(sizeof(char *));

			al[i] = malloc((strlen(token)+1)*sizeof(char));
			strcpy(al[i],token);
			i++;
			token = strtok(NULL,",");
		}
		na=i;
		p = planta_nova(id,nc,al,na,ns);
		j = planta_insere(c,p);
		
		if(j==1)
			planta_apaga(p);

		for(cont=0;cont<i;cont++)
		{
			free(al[cont]);
		}
		if(i!=0)
			free(al);
	}
	fclose(f);

	return c;
}
planta *planta_remove(colecao *c, const char *nomep)
{
	int cont,i;
	int sinal=0;
	planta *p;
	planta *aux;
	
	if(c == NULL)
		return NULL;

	for(cont = 0;cont < c->tamanho;cont++)
	{
		if(strcmp(c->plantas[cont]->nome_cientifico,nomep)==0)
		{
			p=c->plantas[cont];
			i=cont;
			sinal=1;
		}
	}

	if(sinal == 0)
		return NULL;

	for(cont=i;cont<c->tamanho-1;cont++)
	{
		c->plantas[i]=c->plantas[i+1];
	}
	c->tamanho--;
	c->plantas = realloc(c->plantas,c->tamanho *sizeof(planta *));
	return p;
}

int planta_apaga(planta *p)
{
	int cont;
	
	if(p==NULL)
		return -1;
	
	else
	{
		for(cont=0;cont<p->n_alcunhas;cont++)
			free(p->alcunhas[cont]);

		
		if(p->alcunhas!=NULL)
			free(p->alcunhas);	
		
		free(p);
		return 0;
	}	
}
int colecao_apaga(colecao *c)
{
	int cont;

	if(c==NULL)
		return -1;
	
	else
	{
		for(cont=0;cont<c->tamanho;cont++)
			planta_apaga(c->plantas[cont]);

		free(c->plantas);
		free(c);
		return 0;
	}
}
int *colecao_pesquisa_nome(colecao *c, const char *nomep, int *tam)
{
	int cont,j;
	int i=0;
	int sinal=0;

	int *pos = malloc(sizeof(int));

	if(c == NULL || nomep == NULL)
		return NULL;

	for(cont=0; cont<c->tamanho; cont++)
	{
		if(strcmp(c->plantas[cont]->nome_cientifico,nomep)==0)
		{
			if(i!=0)
				pos = realloc(pos, sizeof(int) * (i+1));
			
			pos[i]=cont;
			i++;
			sinal=1;
			continue;
		}
		for(j=0;j<c->plantas[cont]->n_alcunhas;j++)
		{
			if(strcmp(c->plantas[cont]->alcunhas[j],nomep)==0)
			{
				if(i!=0)
					pos = realloc(pos, sizeof(int) * (i+1));
				
				pos[i]=cont;
				i++;
				sinal=1;
				break;
			}
		}
	}
	if(sinal==0)
	{
		free(pos);
		return NULL;
	}

	*tam = i;

	return pos;
}

void IDordenacaoInsercao(colecao *c, int left, int right) {
 	
	int i, j;
	planta *temp;

 	for (i = left+1; i < right+1; i++) {
		temp = c->plantas[i];

		for (j = i; j>0 && strcmp(temp->ID,c->plantas[j-1]->ID)<0; j--)
 			c->plantas[j] = c->plantas[j-1];
		
		c->plantas[j] = temp;
	}
}

void IDquickSortIter(colecao *c, int left, int right) {
 	
	int i, j, tamanho = right-left+1;;
	planta *new;

	if(tamanho<2) 
 		return;
	
	if (tamanho <= 20) 
		IDordenacaoInsercao(c, left, right);
	else {

		int pos = rand()%tamanho + left;
		
		new = c->plantas[pos];
		c->plantas[pos]=c->plantas[right];
		c->plantas[right]=new;

		i = left; j = right-1;

		while(1) {
			while (i < right && strcmp(c->plantas[i]->ID, c->plantas[right]->ID)<=0) 
				i++;
			while (j >= 0 && strcmp(c->plantas[right]->ID, c->plantas[j]->ID)<=0)
				j--;
			if (i < j)
			{
				new = c->plantas[i];
				c->plantas[i]=c->plantas[j];
				c->plantas[j]=new;
			}
			else 
				break;
		}

		new = c->plantas[i];
		c->plantas[i]=c->plantas[right];
		c->plantas[right]=new;
		IDquickSortIter(c, left, i-1);
		IDquickSortIter(c, i+1, right);
	}
}
void NOMECordenacaoInsercao(colecao *c, int left, int right) {
 	
	int i, j;
	planta *temp;

 	for (i = left+1; i < right+1; i++) {
		temp = c->plantas[i];

		for (j = i; j>0 && strcmp(temp->nome_cientifico,c->plantas[j-1]->nome_cientifico)<0; j--)
 			c->plantas[j] = c->plantas[j-1];
		
		c->plantas[j] = temp;
	}
}
void NOMECquickSortIter(colecao *c, int left, int right) {
 	
	int i, j, tamanho = right-left+1;;
	planta *new;

	if(tamanho<2) 
 		return;
	
	if (tamanho <= 20) 
		NOMECordenacaoInsercao(c, left, right);
	else {

		int pos = rand()%tamanho + left;
		
		new = c->plantas[pos];
		c->plantas[pos]=c->plantas[right];
		c->plantas[right]=new;

		i = left; j = right-1;

		while(1) {
			while (i < right && strcmp(c->plantas[i]->nome_cientifico, c->plantas[right]->nome_cientifico)<=0) 
				i++;
			while (j >= 0 && strcmp(c->plantas[right]->nome_cientifico, c->plantas[j]->nome_cientifico)<=0)
				j--;
			if (i < j)
			{
				new = c->plantas[i];
				c->plantas[i]=c->plantas[j];
				c->plantas[j]=new;
			}
			else 
				break;
		}

		new = c->plantas[i];
		c->plantas[i]=c->plantas[right];
		c->plantas[right]=new;
		NOMECquickSortIter(c, left, i-1);
		NOMECquickSortIter(c, i+1, right);
	}
}
 
int colecao_reordena(colecao *c, const char *tipo_ordem){
	
	if(c==NULL)
		return -1;

	if(strcmp(c->tipo_ordem, tipo_ordem)==0)
		return 0;

	strcpy(c->tipo_ordem, tipo_ordem);

	if(strcmp(tipo_ordem, "id")==0){
		IDquickSortIter(c, 0 , c->tamanho-1);
		return 1;
	}
	if(strcmp(tipo_ordem, "nome")==0){
		NOMECquickSortIter(c, 0 , c->tamanho-1);
		return 1;
	}
	else 
		return -1;
	

}


