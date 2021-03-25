/*****************************************************************/
/*          Biblioteca plantas | PROG2 | MIEEC | 2020/21         */
/*****************************************************************/

#include "plantas.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

planta *planta_nova(const char *ID, const char *nome_cientifico, char **alcunhas, int n_alcunhas, int n_sementes)
{
	planta *plant;
	int i;
	plant = malloc(sizeof(planta));
	if(plant==NULL){return NULL;}

	strcpy(plant->ID,ID);
	strcpy(plant->nome_cientifico,nome_cientifico);

	
	if(alcunhas!=NULL){
		plant->alcunhas=malloc(n_alcunhas*sizeof(char*));
		for(i=0;i<n_alcunhas;i++){
			plant->alcunhas[i]=malloc((strlen(alcunhas[i])+1)*sizeof(char));
			strcpy(plant->alcunhas[i],alcunhas[i]);
		}
	}else{plant->alcunhas=NULL;}
	
	plant->n_alcunhas=n_alcunhas;

	plant->n_sementes=n_sementes;


	return plant;
}

colecao *colecao_nova(const char *tipo_ordem)
{
	colecao *c;
	c=malloc(sizeof(colecao));
	if(c==NULL){return NULL;}

	c->plantas=NULL;
	c->tamanho=0;
	strcpy(c->tipo_ordem,tipo_ordem);

	return c;
}
int planta_insere(colecao *c, planta *p)
{
	int tamanhoc=c->tamanho,i,exists=0;
	if(c==NULL || p==NULL){return -1;}
	
	
	//caso de ser a primeira planta na coleção
	if(tamanhoc==0){
		c->plantas=malloc(sizeof(planta*));
		c->plantas[0]=p;
		c->tamanho++;
		return 0;
	}

	for(i=0;i<tamanhoc;i++){ //goes trough c->plantas
		if(strcmp(c->plantas[i]->ID,p->ID)==0){ //checks if plant already exits in coletion
			c->plantas[i]->n_sementes+=p->n_sementes; //add seed count
			
			int acolecao, aplanta;
			for(aplanta=0;aplanta<p->n_alcunhas;aplanta++){	//for every alcunha in c->planta[i]->alcunhas goes trough every alcunha in planta->alcunhas
				exists=0;
				for(acolecao=0;acolecao<c->plantas[i]->n_alcunhas;acolecao++){
					if(strcmp(c->plantas[i]->alcunhas[acolecao],p->alcunhas[aplanta])==0){ //checks if p-alcunha[aplanta] doesn't exists in c->plantas[i]->alcunhas[acolecao]
						exists=1;
						break;
					}
				}
				if(!exists){
					if(c->plantas[i]->n_alcunhas==0){
						c->plantas[i]->alcunhas=malloc(sizeof(char*));
					}
					else{
						c->plantas[i]->alcunhas=realloc(c->plantas[i]->alcunhas,(c->plantas[i]->n_alcunhas+1)*sizeof(char*));
					}
					c->plantas[i]->alcunhas[c->plantas[i]->n_alcunhas]=malloc((strlen(p->alcunhas[aplanta])+1)*sizeof(char));
					strcpy(c->plantas[i]->alcunhas[c->plantas[i]->n_alcunhas],p->alcunhas[aplanta]);
					c->plantas[i]->n_alcunhas++;
				}

			}
			exists=1;
			break;
		}
	}
	if(exists){return 1;}

	int pos=-1;
	if (strcmp(c->tipo_ordem,"id")==0){
		for(i=0;i<tamanhoc;i++){
			if(strcmp(c->plantas[i]->ID,p->ID)>0){
				pos=i;
				break;
			}
		}
	}
	else if (strcmp(c->tipo_ordem,"nome")==0){
		for(i=0;i<tamanhoc;i++){
			if(strcmp(c->plantas[i]->nome_cientifico,p->nome_cientifico)>0){
				pos=i;
				break;
			}
		}
	}
	else{return -1;}
	c->tamanho++;
	tamanhoc=c->tamanho;
	c->plantas=realloc(c->plantas,(tamanhoc)*sizeof(planta*));
	if (pos==-1){
		c->plantas[tamanhoc-1]=p;
		return 0;
	}
	else{
		for(i=tamanhoc-1;i>pos;i--){
			c->plantas[i]=c->plantas[i-1];
		}
		c->plantas[pos]=p;
		return 0;
	}
	
	return -1;
}


int colecao_tamanho(colecao *c)
{
	if(c==NULL){return -1;}

	return c->tamanho;
}

colecao *colecao_importa(const char *nome_ficheiro, const char *tipo_ordem)
{
	colecao *c;
	planta *p;
	FILE *f;
	char linha[400],*token,ID[10], nome[MAX_NAME],*token_anterior;
	int n_seeds,n_alcunhas,i,check;
	f=fopen(nome_ficheiro,"r");
	c=colecao_nova(tipo_ordem);

	if(c==NULL ||f==NULL){return NULL;}
	char **alcunhas;
	while(fgets(linha,400,f)!=NULL){
		token=strtok(linha,"\n");
		memmove(linha,token,strlen(linha));

		token=strtok(linha,",");
		strcpy(ID,token);
		
		token=strtok(NULL,",");
		strcpy(nome,token);
		
		token=strtok(NULL,",");
		n_seeds=atoi(token);

		alcunhas=NULL;
		n_alcunhas=0;
		
		token=strtok(NULL,","); 
		if(token!=NULL){	//it means alcunhas exists
			alcunhas=malloc(sizeof(char*));
			alcunhas[0]=malloc((strlen(token)+1)*sizeof(char));
			strcpy(alcunhas[0],token);
			n_alcunhas++;
			token=strtok(NULL,",");
			while(token!=NULL){
				alcunhas=realloc(alcunhas,(n_alcunhas+1)*sizeof(char*));
				alcunhas[n_alcunhas]=malloc((strlen(token)+1)*sizeof(char));
				if(alcunhas[n_alcunhas]==NULL){return NULL;}
				strcpy(alcunhas[n_alcunhas],token);
				n_alcunhas++;
				token=strtok(NULL,",");
			}
		}
		p=planta_nova(ID,nome,alcunhas,n_alcunhas,n_seeds);
		if(p==NULL){return NULL;}
		check=planta_insere(c,p);
		if(check==-1){return NULL;}
		else if(check==1){planta_apaga(p);}
		p=NULL;
		for(i=0;i<n_alcunhas;i++){
			free(alcunhas[i]);
		}
		free(alcunhas);
	}
	fclose(f);
	return c;
}
planta *planta_remove(colecao *c, const char *nomep)
{
	int tamanhoc=c->tamanho,i,exists=0,pos;
	planta *pr;
	if(c==NULL){return NULL;}
	for(i=0;i<tamanhoc;i++){
		if(strcmp(c->plantas[i]->nome_cientifico,nomep)==0){
			exists=1;
			pr=c->plantas[i];
			pos=i;
			break;
		}
	}
	if(!exists){return NULL;}

	for(i=pos;i<tamanhoc-1;i++){
		c->plantas[i]=c->plantas[i+1];
	}
	c->tamanho--;
	
	c->plantas=realloc(c->plantas,c->tamanho*sizeof(planta*));

	return pr;
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
int colecao_reordena(colecao *c, const char *tipo_ordem)
{
	if(c==NULL){return -1;}
	if(strcmp(c->tipo_ordem,tipo_ordem)==0 || c->tamanho==0 || c->tamanho==1){return 0;}

	
	int tamanhoc=c->tamanho,i,a;
	planta *aux;
	if(strcmp(tipo_ordem,"nome")==0){
		for(i=0;i<tamanhoc;i++){
			for(a=0;a<tamanhoc;a++){
				if(strcmp(c->plantas[i]->nome_cientifico,c->plantas[a]->nome_cientifico)<0){
					aux=c->plantas[i];
					c->plantas[i]=c->plantas[a];
					c->plantas[a]=aux;
				}
			}
		}
		strcpy(c->tipo_ordem,tipo_ordem);
		return 1;
	}
	else if(strcmp(tipo_ordem,"id")==0){
		for(i=0;i<tamanhoc;i++){
			for(a=0;a<tamanhoc;a++){
				if(strcmp(c->plantas[i]->ID,c->plantas[a]->ID)<0){
					aux=c->plantas[i];
					c->plantas[i]=c->plantas[a];
					c->plantas[a]=aux;
				}
			}
		}
		strcpy(c->tipo_ordem,tipo_ordem);
		return 1;
	}
	else{return -1;}
}
