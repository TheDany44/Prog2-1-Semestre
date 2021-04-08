/*****************************************************************/
/*          Biblioteca plantas | PROG2 | MIEEC | 2020/21         */
/*****************************************************************/

#include "plantas.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

planta *planta_nova(const char *ID, const char *nome_cientifico, char **alcunhas, int n_alcunhas, int n_sementes)
{
	planta *pl_nova = (planta *) malloc(sizeof(planta));

	if(pl_nova == NULL)
		return NULL;

	strcpy(pl_nova->ID,ID);
	strcpy(pl_nova->nome_cientifico,nome_cientifico);

	pl_nova->n_sementes = n_sementes;
	pl_nova->n_alcunhas = n_alcunhas;

	if(alcunhas == NULL){ 
		pl_nova->alcunhas = NULL;
	}
	else{ 
		pl_nova->alcunhas=(char**)malloc(n_alcunhas*(sizeof(char*)));

		for(int i = 0; i < n_alcunhas; i++)
		{
			pl_nova->alcunhas[i] = (char *) malloc((strlen(alcunhas[i])+1)*sizeof(char));
			strcpy(pl_nova->alcunhas[i], alcunhas[i]);
		}
	}

	return pl_nova;
}

colecao *colecao_nova(const char *tipo_ordem)
{
	colecao *col_nova = (colecao*) malloc(sizeof(colecao));
	
	if(col_nova == NULL)
		return NULL;

	col_nova->tamanho = 0;

	strcpy(col_nova->tipo_ordem, tipo_ordem);
	col_nova->plantas = NULL; //para que serve

	return col_nova;
}
int planta_insere(colecao *c, planta *p)
{
	if(c == NULL || p == NULL)
		return -1;
	
	//planta ja existe (id=) (+n_sementes) (+novas alcunhas)
	planta *pl_atual;
	char* alcunha_atual;
	int j, x, final_lista, tam_alcunha, ja_existe = 5, alcunhacontrol; //variavel de controlo
	
	for(int i = 0; i < c->tamanho; i++){

		if (strcmp(c->plantas[i]->ID, p->ID ) == 0){
			ja_existe = 3;
			c->plantas[i]->n_sementes += p->n_sementes;
			pl_atual = c->plantas[i];
		
			for(j=0; j < p->n_alcunhas; j++){
				alcunha_atual = p->alcunhas[j];
				alcunhacontrol = 0;
				tam_alcunha = pl_atual->n_alcunhas;

				for(x = 0; x < tam_alcunha; x++){
					if(strcmp(pl_atual->alcunhas[x], alcunha_atual) == 0){
						alcunhacontrol = 1;
					}
				}
				
				if(alcunhacontrol == 0){ 
					pl_atual->n_alcunhas++;
					pl_atual->alcunhas= (char **) realloc(pl_atual->alcunhas, (pl_atual->n_alcunhas)*sizeof(char *));
					final_lista = pl_atual->n_alcunhas - 1;
					pl_atual->alcunhas[final_lista] = (char*) malloc((strlen(alcunha_atual)+1)*sizeof(char));

					strcpy(pl_atual->alcunhas[final_lista], alcunha_atual);
				}
			}
		}
	}
	if(ja_existe == 3) 
		return 1;
	
	planta* p1;
	int tam;
	int k,i=0,fim=0;
	tam = c->tamanho;
	
	//alocar espaço necessario para juntar a planta
	if(c->tamanho == 0)
	{
		c->plantas = (planta**)malloc(sizeof(planta*));
	}
	else 
	{ 
		c->plantas = (planta**)realloc(c->plantas,(c->tamanho + 1)*sizeof(planta*));
	}
	//acrescenta no lugar certo
	if (strcmp(c->tipo_ordem, "id") == 0)
	{
		c->tamanho++;
		for(k = 0; k < tam; k++)
		{
			p1 = c->plantas[k];
			if (strcmp(p1->ID, p->ID) > 0){
				fim = 1;
				for(i = tam; i > k; i--)
				{
					c->plantas[i] = c->plantas[i-1];
				}
				c->plantas[k] = p;
				break;
			}
		}	
		if(tam == 0) //colocar no inicio
		{
			c->plantas[0] = p;
		}
		if(fim == 0) //colocar no final
		{
			c->plantas[tam] = p;
		}
		return 0;
	}
	
	else if (strcmp(c->tipo_ordem,"nome") == 0){
		c->tamanho++;
		for(k = 0;k < tam; k++){
			p1 = c->plantas[k];
			if(strcmp(p1->nome_cientifico,p->nome_cientifico)>0){
				fim = 1;
				for(i = tam-1; i >= k; i--){
					c->plantas[i+1] = c->plantas[i];
				}
				c->plantas[k] = p;
				break;
			}
		}
		if(tam == 0){
			c->plantas[0] = p;
		}
		if(fim == 0){
			c->plantas[tam] = p;
		}
		return 0;
	}
	return -1;
}
int colecao_tamanho(colecao *c)
{
	if(c == NULL)  
		return -1;

	return c->tamanho;
}

colecao *colecao_importa(const char *nome_ficheiro, const char *tipo_ordem)
{
	
	//ler o ficheiro 
	//copiar os valores de cada linha para uma planta 
	//colocar numa coleção

	FILE* f;
	planta *p;
	colecao *c;
	c = colecao_nova(tipo_ordem);
	char linha[500],*token, ID[10], nome_cientifico[MAX_NAME],**alcunhas;
	int i, n_sementes, n_alcunhas;

	f = fopen(nome_ficheiro,"r");

	while(fgets(linha, 500, f) != NULL){
		
		linha[ strlen(linha) - 1] = '\0';
		
		n_alcunhas = 0;
		alcunhas = NULL;
		
		token = strtok(linha,",");
		strcpy(ID,token);

		token = strtok(NULL,",");
		strcpy(nome_cientifico,token);
		
		token = strtok(NULL,",");
		n_sementes = atoi(token);

		token = strtok(NULL,",");

		while(token != NULL)
		{
			if(alcunhas == NULL){
				alcunhas = (char**)malloc(sizeof(char*));
			}
			else{
				alcunhas = (char**)realloc(alcunhas,sizeof(char*)*(n_alcunhas + 1));
			}	
			n_alcunhas++;
			alcunhas[n_alcunhas - 1] = (char*)malloc((strlen(token) + 1)*(sizeof(char)));
			strcpy(alcunhas[n_alcunhas-1],token);
			token = strtok(NULL,",");
		}
		
		p = planta_nova(ID, nome_cientifico, alcunhas, n_alcunhas, n_sementes);
		
		if(planta_insere(c , p) == 1){
			planta_apaga(p); //se ja existe
		}
		for(i = 0; i < n_alcunhas; i++){
			free(alcunhas[i]);
		}
		p = NULL;//resetar a variavel da planta
		if(n_alcunhas != 0)
			free(alcunhas);
	}
	fclose(f);

	return c;
}
planta *planta_remove(colecao *c, const char *nomep)
{
	if(c == NULL )  
		return NULL;

	int i, pos;
	planta *ptr;
	int ja_encontrou = 5; //variavel de controlo

	for(i = 0; i < c->tamanho; i++){
		if(strcmp(c->plantas[i]->nome_cientifico, nomep) == 0){
			ptr = c->plantas[i]; //guarda endereço
			pos = i;
			ja_encontrou = 3;
		}
	}
	if(ja_encontrou != 3)
		return NULL;
			
	//corrige coleçao
	c->tamanho--;
	for(i = pos; i < c->tamanho; i++)
		c->plantas[i] = c->plantas[i+1];
		
	c->plantas = (planta**)realloc(c->plantas,c->tamanho*sizeof(planta*));
	
	return ptr;
}

int planta_apaga(planta *p)
{
	int i;

	if(p == NULL)
		return -1;

	if(p->n_alcunhas != 0){ 
		for(i = 0; i < p->n_alcunhas; i++){
			free(p->alcunhas[i]);
		}
	}
	free(p->alcunhas);  
	free(p);
	
	return 0;
}
int colecao_apaga(colecao *c)
{
	int i;

	if(c == NULL)
		return -1;

	for (i = 0; i < c->tamanho; i++){
		planta_apaga(c->plantas[i]);
	}

	free(c->plantas);
	free(c);
	
	return 0;
}
int *colecao_pesquisa_nome(colecao *c, const char *nomep, int *tam)
{ 
	if(c == NULL)
		return NULL; 

	int i, j, *vetor_indices;
	*tam = 0;
	vetor_indices = NULL;

	//pesquisa sequencial
	for (i = 0; i < c->tamanho; i++)
	{
		if (strcmp(c->plantas[i]->nome_cientifico, nomep) == 0){
			(*tam)++;
			vetor_indices = (int*)realloc(vetor_indices,sizeof(int*)*(*tam));
			vetor_indices[*tam-1]=i;
		}
		for(j = 0; j < c->plantas[i]->n_alcunhas; j++){
			if(strcmp(c->plantas[i]->alcunhas[j],nomep)==0){
				(*tam)++;
				vetor_indices = (int*)realloc(vetor_indices,sizeof(int*)*(*tam));
				vetor_indices[*tam-1]=i;
			}
		}
	}
	return vetor_indices;	
	
}

void quickSortIter(planta **p, int left, int right, const char *tipo_ordem) {

	int i, j, tamanho = right - left + 1;
	planta *trocap;
 	if(tamanho < 2) //com tamanho 0 ou 1 esta ordenado 
 		return;
	
 	if(tamanho < 20){
		planta *aux;
 		for (i = left+1; i < right + 1; i++) {
			aux = p[i];
			if(strcmp(tipo_ordem, "nome") == 0){
				for (j = i; j > 0 && strcmp(aux->nome_cientifico,p[j-1]->nome_cientifico) < 0; j--){ 
					p[j] = p[j-1];
				}
			}
			else if (strcmp(tipo_ordem, "id") == 0){
				for (j = i; j > 0 && strcmp(aux->ID,p[j-1]->ID) < 0; j--){
					p[j] = p[j-1];
				}
			}
			p[j] = aux;
		}
	}
	else { 
 		int pos = (rand() % tamanho) + left; //determina pivot 
 		trocap=p[pos];
		p[pos]=p[right];
		p[right]=trocap;
		 //troca(p[pos], p[right]); //coloca pivot no fim 
 		i = left; j = right-1; //passo de partição 

 		while(1) {
			if(strcmp(tipo_ordem, "nome") == 0){
				while (i < right && strcmp(p[i]->nome_cientifico, p[right]->nome_cientifico) <= 0)
					i++;
				while (j >= 0 && strcmp(p[right]->nome_cientifico, p[j]->nome_cientifico) <= 0)
					j--;
			}
			else if (strcmp(tipo_ordem, "id") == 0){
				while (i < right && strcmp(p[i]->ID, p[right]->ID) <= 0)
					i++;
				while (j >= 0 && strcmp(p[right]->ID, p[j]->ID) <= 0)
					j--;
			}
			if (i < j){
				trocap=p[i];
				p[i]=p[j];
				p[j]=trocap;
				//troca(p[i], p[j]);
			}
 			else{
				break;
			}
		}
		trocap=p[pos];
		p[pos]=p[right];
		p[right]=trocap;
 		//troca(p[i], p[right]); // repoe pivot
 		quickSortIter(p, left, i-1, tipo_ordem);
 		quickSortIter(p, i+1, right, tipo_ordem);
 	}
 }


int colecao_reordena(colecao *c, const char *tipo_ordem){

	if(c == NULL || ((strcmp(c->tipo_ordem, "nome") != 0) && strcmp(c->tipo_ordem, "id") != 0))
		return -1;	
			
	if(strcmp(c->tipo_ordem, tipo_ordem) == 0) // ja esta ordenado  
		return 0;

	else {
		quickSortIter(c->plantas, 0, c->tamanho - 1, tipo_ordem);
	}
	strcpy(c->tipo_ordem, tipo_ordem); 
		return 1;
}
	