/******************************************************************/
/*          Biblioteca plantas | PROG2 | MIEEC | 2020/21          */
/******************************************************************/
//versao 28/03

#include "plantas.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


planta *planta_nova(const char *ID, const char *nome_cientifico, char **alcunhas, int n_alcunhas, int n_sementes) //cria uma nova planta com os valores dos parametros
{
	if(ID==NULL || nome_cientifico==NULL || n_alcunhas<0){return NULL;}
	planta *plant; //criacao de um novo apontador para planta com nome diferente
	plant = malloc(sizeof(planta)); //alocacao dinamica de memoria do apontador plant
	if(plant==NULL){return NULL;} //retorna NULL se ocorrer algum erro, neste caso quando plant nao existe == NULL 
	int i;

	strcpy(plant->ID,ID);
	strcpy(plant->nome_cientifico,nome_cientifico);


	if(alcunhas!=NULL){
		plant->alcunhas=malloc(n_alcunhas*sizeof(char*));
		if(plant->alcunhas==NULL){free(plant);return NULL;}
		for(i=0;i<n_alcunhas;i++){
			plant->alcunhas[i]=malloc((strlen(alcunhas[i])+1)*sizeof(char));
			if(plant->alcunhas[i]==NULL){free(plant);int k;for(k=0;k<i;k++){free(plant->alcunhas[k]);} free(plant->alcunhas);return NULL;}
			strcpy(plant->alcunhas[i],alcunhas[i]);
		}
	}else{plant->alcunhas=NULL;}

	plant->n_alcunhas=n_alcunhas;

	plant->n_sementes=n_sementes;


	return plant; //em caso de sucesso retorna o apontador para a planta criada
}


colecao *colecao_nova(const char *tipo_ordem) //cria uma nova colecao vazia
{
	if(tipo_ordem==NULL){return NULL;} //tipo_ordem é uma string que contem o tipo de ordenacao da nova colecao
	colecao *c; //cria apontador para a colecao
	c=malloc(sizeof(colecao)); //aloca dinamicamente memoria do apontador para colecao
	if(c==NULL){return NULL;} //se ocorreu algum erro retornar NULL

	c->plantas=NULL;
	c->tamanho=0;
	strcpy(c->tipo_ordem,tipo_ordem);

	return c; //em caso de sucesso retorna apontador para a colecao criado anteriormente
}


planta *procurar_planta(colecao *c,planta *p){
	if(c==NULL || p==NULL){return NULL;} //se c==NULL ou p==NULL retorna NULL

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


int pesquisa_alcunha(planta *p,char *alcunha){ //pesquisa alcunha mediante parametros de entrada, p é apontador para planta
	if(p==NULL || alcunha==NULL){return -2;} //se nao existir apontador para planta ou nao houver alcunha, retorna -2
	int i;
	for(i=0;i<p->n_alcunhas;i++){
		if(strcmp(p->alcunhas[i],alcunha)==0){
			return i; //i é a pçosicao onde esta a alcunha que queremos
		}
	}
	return -1;
}


int planta_insere(colecao *c, planta *p) //insere uma planta na colecao, na posicao correta de acordo com o tipo_ordem
{
	if(c==NULL || p==NULL){return -1;} //c é o apontador para a colecao, p é a planta a inserir
	int tamanhoc=c->tamanho,i,control=-1;
	planta* planta_encontrada;
	planta_encontrada=NULL;

	//caso de ser a primeira planta na coleção
	if(tamanhoc==0){
		c->plantas=malloc(sizeof(planta*));
		if(c->plantas==NULL){return -1;}
		c->plantas[0]=p;
		c->tamanho++;
		return 0; //retorna 0 se a planta nao existia e foi inserida com sucesso
	}

	planta_encontrada=procurar_planta(c,p);

	if(planta_encontrada!=NULL){
		planta_encontrada->n_sementes+=p->n_sementes; //adiciona contador de sementes

		for(i=0;i<p->n_alcunhas;i++){
			control=pesquisa_alcunha(planta_encontrada,p->alcunhas[i]);

			if(control==-1){
				if(planta_encontrada->n_alcunhas==0){
					planta_encontrada->alcunhas=malloc(sizeof(char*));
					if(planta_encontrada->alcunhas==NULL){return -1;}
				}
				else{
					planta_encontrada->alcunhas=realloc(planta_encontrada->alcunhas,(planta_encontrada->n_alcunhas+1)*sizeof(char*));
					if(planta_encontrada->alcunhas==NULL){return -1;}
				}

				planta_encontrada->alcunhas[planta_encontrada->n_alcunhas]=malloc((strlen(p->alcunhas[i])+1)*sizeof(char));
				if(planta_encontrada->alcunhas[planta_encontrada->n_alcunhas]==NULL){return -1;}
				strcpy(planta_encontrada->alcunhas[planta_encontrada->n_alcunhas],p->alcunhas[i]);
				planta_encontrada->n_alcunhas++;
			}
		}
		return 1; //retorna 1 se a planta ja existia e apenas foi atualizada
	}


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
	if(c->plantas==NULL){return -1;}
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

	return -1; //retorna -1 se ocorrer algum erro
}


int colecao_tamanho(colecao *c) //indica o numero de plantas na colecao
{
	if(c==NULL){return -1;} //se houver algum erro de importacao retorna -1

	return c->tamanho; //se sucesso retorna numero de plantas da colecao
}


colecao *colecao_importa(const char *nome_ficheiro, const char *tipo_ordem) //cria uma colecao, le o conteudo do ficheiro de texto de nome nome_ficheiro e importa-o para a colecao criada
{
	colecao *c; //criada uma colecao
	FILE *f; //criar apontador para ficheiro
	planta *p; //criar apontador planta struct
	char linha[700],*token,ID[10], nome[MAX_NAME];
	int n_seeds,n_alcunhas,i,check;
	f=fopen(nome_ficheiro,"r"); //nome_ficheiro é nome do ficheiro de texto contendo a colecao a importar, aberto em reading mode
	if(f==NULL){return NULL;} 
	c=colecao_nova(tipo_ordem); //tipo_ordem é o tipo de ordenacao da nova colecao
	if(c==NULL){return NULL;}

	char **alcunhas;
	while(fgets(linha,700,f)!=NULL){
		n_seeds=0;

		linha[strlen(linha)-1]='\0';

		token=strtok(linha,",");
		if(token==NULL){continue;}
		strcpy(ID,token);

		token=strtok(NULL,",");
		if(token==NULL){continue;}
		strcpy(nome,token);

		token=strtok(NULL,",");
		if(token==NULL){continue;}
		n_seeds=atoi(token);
		if(n_seeds==0){continue;}

		alcunhas=NULL;
		n_alcunhas=0;

		token=strtok(NULL,",");
		if(token!=NULL){ //significa que alcunhas existe
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


int procurar_planta_nome(colecao *c,const char* nome){ //serve para procurar char nome na planta apontada pelo apontador c
	if(c==NULL || nome==NULL){return -2;} //se c==NULL ou nome==NULL retorna -2

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


planta *planta_remove(colecao *c, const char *nomep) //remove da colecao a planta com nome cientifico dado por nomep e corrige a colecao no elemento retirado
{
	int tamanhoc=c->tamanho,i,pos;
	planta *pr; //pr é apontador para planta
	if(c==NULL){return NULL;} //retornado NULL se ocorrer um erro ou c não existir

	pos=procurar_planta_nome(c,nomep); //c é apontador para a colecao, nomp é nome cientifico da planta a ser removido
	if(pos<0){return NULL;}
	pr=c->plantas[pos];

	for(i=pos;i<tamanhoc-1;i++){
		c->plantas[i]=c->plantas[i+1];
	}
	c->tamanho--;

	c->plantas=realloc(c->plantas,c->tamanho*sizeof(planta*));

	return pr; //em caso de sucesso é retornado o apontador para a planta removida da colecao
}


int planta_apaga(planta *p) //elimina uma planta, libertando toda a memoria por ela ocupada
{
	int i;
	if(p==NULL){return -1;} //retornar -1 em caso de erro, neste caso quando p não existe == NULL

	if(p->n_alcunhas!=0){ //p é o apontador para a planta
		for(i=0;i<p->n_alcunhas;i++){
			free(p->alcunhas[i]);
		}
		free(p->alcunhas);
	}

	free(p);
	p=NULL;

	return 0; //retornar 0 se a remocao ocorrer com sucesso
}
int colecao_apaga(colecao *c) //elimina uma colecao, libertando toda a memoria por ela ocupada
{
	if(c==NULL){return -1;} //retornar -1 em caso de insucesso, neste caso quando c não existe == NULL

	int tamanhoc=c->tamanho,i;
	for(i=0;i<tamanhoc;i++){ //elimina todas as plantas da colecao de plantas, uma a uma com uma expressao for(para i=0 enqaunto que i não chega até ao fim da colecao adiciona +1)
		planta_apaga(c->plantas[i]);
	}
	free(c->plantas); //liberta espaco alocado de c->plantas
	free(c); //liberta espaco alocado de c (apontador para a colecao)

	return 0; //retornar 0 se a remocao da colecao for bem sucedida
}
int *colecao_pesquisa_nome(colecao *c, const char *nomep, int *tam) //reordena a colecao de acordo com o tipo_ordem; ‘nome’ - ordena alfabeticamente por nome_cientifico; ‘id’ - ordena alfabeticamente pelo campo de identificacao unica
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
	return pos; //retorna o vetor de indices/posicoes das plantas encontradas
}


void Quick_Sort_colecao(colecao *c,int left,int right){ //funcao de ordenacao rapida para colecao, left=0
	int i, k;
	planta *ptemp;
	if(right-left+1<2){return;} //right é o fim, left é o inicio da colecao... 
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


int colecao_reordena(colecao *c, const char *tipo_ordem) //reordena a colecao de acordo com o tipo_ordem; ‘nome’ - ordena alfabeticamente por nome_cientifico; ‘id’ - ordena alfabeticamente pelo campo de identificacao unica
{
	if(c==NULL){return -1;} //retorna -1 em caso de erro
	if(strcmp(c->tipo_ordem,tipo_ordem)==0 || c->tamanho==0 || c->tamanho==1){return 0;} //retorna 0 se nao for necessario reordenar

	strcpy(c->tipo_ordem,tipo_ordem);
	Quick_Sort_colecao(c,0,c->tamanho-1);
	return 1; //retorna 1 se for necessario reordenar e a reordenacao ocorrer com sucesso

}
