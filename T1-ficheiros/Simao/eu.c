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

planta *procurar_planta(colecao *c,planta *p){
	if(c==NULL || p==NULL){return NULL;}

	int left=0, right=c->tamanho-1,mid;
	if (strcmp(c->tipo_ordem,"id")==0){ 
		while(left<=right){
			mid=(left+right)/2;
			if(strcmp(c->plantas[mid]->ID,p->ID)==0){
				return c->plantas[mid];
			}
			else if(strcmp(p->ID,c->plantas[mid]->ID)<0){
				right=mid-1;
			}
			else{
				left=mid+1;
			}
		}
		return NULL;
	}
	else if (strcmp(c->tipo_ordem,"nome")==0){
		while(left<=right){
			mid=(left+right)/2;
			if(strcmp(c->plantas[mid]->nome_cientifico,p->nome_cientifico)==0){
				return c->plantas[mid];
			}
			else if(strcmp(p->nome_cientifico,c->plantas[mid]->nome_cientifico)<0){
				right=mid-1;
			}
			else{
				left=mid+1;
			}
		}
		return NULL;
	}
	return NULL;

}

int pesquisa_alcunha(planta *p,char *alcunha){
	if(p==NULL || alcunha==NULL){return -2;}
	int i;
	for(i=0;i<p->n_alcunhas;i++){
		if(strcmp(p->alcunhas[i],alcunha)==0){
			return i;
		}
	}
	return -1;
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
		strcpy(c->tipo_ordem, "nome");
		
	}
		
	
	if(strcmp(c->tipo_ordem,"id")==0){
		strcpy(c->tipo_ordem, "nome");
		
		colecao_reordena(c, "id");
		strcpy(c->tipo_ordem, "id");
		
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

int procurar_planta_nome(colecao *c,const char* nome){
	if(c==NULL || nome==NULL){return -2;}

	if (strcmp(c->tipo_ordem,"id")==0){ 
		int i;
		for(i=0;i<c->tamanho;i++){
			if(strcmp(c->plantas[i]->nome_cientifico,nome)==0){
				return i;
			}
		}
	}
	else if (strcmp(c->tipo_ordem,"nome")==0){
		int left=0, right=c->tamanho-1,mid;
		while(left<=right){
			mid=(left+right)/2;
			if(strcmp(c->plantas[mid]->nome_cientifico,nome)==0){
				return mid;
			}
			else if(strcmp(nome,c->plantas[mid]->nome_cientifico)<0){
				right=mid-1;
			}
			else{
				left=mid+1;
			}
		}
		return -1;
	}
	return -2;

}

planta *planta_remove(colecao *c, const char *nomep)
{
	int cont,i;
	int sinal=0;
	planta *p;
	
	if(c == NULL)
		return NULL;

	for(cont = 0;cont < c->tamanho;cont++)
	{
		if(strcmp(c->plantas[cont]->nome_cientifico,nomep)==0)
		{
			p=c->plantas[cont];
			i=cont;
			sinal=1;
			break;
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
	int i;
	if(p==NULL){return -1;}

	if(p->n_alcunhas!=0){ 
		for(i=0;i<p->n_alcunhas;i++){
			free(p->alcunhas[i]);
		}
		free(p->alcunhas);
	}
	
	free(p);
	p=NULL;

	return 0;
}
int colecao_apaga(colecao *c)
{
	if(c==NULL){return -1;}

	int tamanhoc=c->tamanho,i;
	for(i=0;i<tamanhoc;i++){
		planta_apaga(c->plantas[i]);
	}
	free(c->plantas);
	free(c);

	return 0;
}
int *colecao_pesquisa_nome(colecao *c, const char *nomep, int *tam)
{
	if(c==NULL){return NULL;}
	int tamanhoc=c->tamanho,i,*pos,exists=0,tamanhov=0,tamanhoa,a;
	pos=NULL;
	for(i=0;i<tamanhoc;i++){
		if(strstr(c->plantas[i]->nome_cientifico,nomep)!=NULL){
			if(pos==NULL){ 
				exists=1;
				pos=malloc(sizeof(int*));
				pos[0]=i;
			}
			else{
				pos=realloc(pos,(tamanhov+1)*sizeof(int*));
				pos[tamanhov]=i;
			}
			tamanhov++;
		}
		else{
			tamanhoa=c->plantas[i]->n_alcunhas;
			for(a=0;a<tamanhoa;a++){
				if(strstr(c->plantas[i]->alcunhas[a],nomep)!=NULL){
					if(pos==NULL){ 
						exists=1;
						pos=malloc(sizeof(int*));
						pos[0]=i;
					}
					else{
						pos=realloc(pos,(tamanhov+1)*sizeof(int*));
						pos[tamanhov]=i;
					}
					tamanhov++;
					break;
				}
			}
		}
	}

	if(exists==0){return NULL;}
	*tam=tamanhov;
	return pos;
}

void Quick_Sort_colecao(colecao *c,int left,int right){
	int i, k;
	planta *ptemp;
	if(right-left+1<2){return;}
	if(strcmp(c->tipo_ordem,"id")==0){ 

		if(right-left+1<20){

			for(i=left+1;i<right+1;i++){
				ptemp=c->plantas[i];
				for(k=i;k>0 && strcmp(ptemp->ID,c->plantas[k-1]->ID)<0;k--){
					c->plantas[k]=c->plantas[k-1];
				}
				c->plantas[k]=ptemp;
			}
		}
		else{
			int pos=rand()%(right-left+1)+left;
			ptemp=c->plantas[pos];
			c->plantas[pos]=c->plantas[right];
			c->plantas[right]=ptemp;

			i=left;
			k=right-1;
			while(1){
				while(i<right && strcmp(c->plantas[i]->ID,c->plantas[right]->ID)<=0){
					i++;
				}
				while(k>=0 && strcmp(c->plantas[right]->ID,c->plantas[k]->ID)<=0){
					k--;
				}
				if(i<k){
					ptemp=c->plantas[i];
					c->plantas[i]=c->plantas[k];
					c->plantas[k]=ptemp;
				}
				else{break;}
			}
			ptemp=c->plantas[i];
			c->plantas[i]=c->plantas[right];
			c->plantas[right]=ptemp;
			Quick_Sort_colecao(c,left,i-1);
			Quick_Sort_colecao(c,i+1,right);
		}
	}
	else if(strcmp(c->tipo_ordem,"nome")==0){ 
		if(right-left+1<20){

			for(i=left+1;i<right+1;i++){
				ptemp=c->plantas[i];
				for(k=i;k>0 && strcmp(ptemp->nome_cientifico,c->plantas[k-1]->nome_cientifico)<0;k--){
					c->plantas[k]=c->plantas[k-1];
				}
				c->plantas[k]=ptemp;
			}
		}
		else{
			int pos=rand()%(right-left+1)+left;
			ptemp=c->plantas[pos];
			c->plantas[pos]=c->plantas[right];
			c->plantas[right]=ptemp;

			i=left;
			k=right-1;
			while(1){
				while(i<right && strcmp(c->plantas[i]->nome_cientifico,c->plantas[right]->nome_cientifico)<=0){
					i++;
				}
				while(k>=0 && strcmp(c->plantas[right]->nome_cientifico,c->plantas[k]->nome_cientifico)<=0){
					k--;
				}
				if(i<k){
					ptemp=c->plantas[i];
					c->plantas[i]=c->plantas[k];
					c->plantas[k]=ptemp;
				}
				else{break;}
			}
			ptemp=c->plantas[i];
			c->plantas[i]=c->plantas[right];
			c->plantas[right]=ptemp;
			Quick_Sort_colecao(c,left,i-1);
			Quick_Sort_colecao(c,i+1,right);
		}
	}
	return;
}


int colecao_reordena(colecao *c, const char *tipo_ordem)
{
	if(c==NULL){return -1;}
	if(strcmp(c->tipo_ordem,tipo_ordem)==0 || c->tamanho==0 || c->tamanho==1){return 0;}

	strcpy(c->tipo_ordem,tipo_ordem);
	Quick_Sort_colecao(c,0,c->tamanho-1);
	return 1;

}
