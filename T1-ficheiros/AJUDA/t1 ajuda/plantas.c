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
    if (p == NULL || c == NULL) return -1;
    
    int tam=(int)c->tamanho;
    int hasFound=0;
    
	printf("\ntam: %d\n",tam);
	printf("\nola1\n");
	
    if(tam>0){
        printf("\nola1.23\n");
        for(int i = 0;i<tam;i++){
            printf("\nola2\n");
            if(strcmp(c->plantas[i]->ID,p->ID)==0){
                //como encontrou um ID igual, vai só somar os valores de *p
                hasFound=1;
                printf("\nola3\n");
                
                //somar numero de sementes:
                c->plantas[i]->n_sementes+=p->n_sementes;
                
                //acrescentar as novas alcunhas:
                int hasEqual=0;

                for(int k = 0;k<(p->n_alcunhas);k++){
                    //verifica se há igual
                    for(int j=0;j<(c->plantas[i]->n_alcunhas);j++){
                        if(strcmp(c->plantas[i]->alcunhas[j],p->alcunhas[k])==0){
                            hasEqual=1;
                        }
                    }
                    if(!hasEqual){
                        *c->plantas[i]->alcunhas[sizeof(c->plantas[i]->alcunhas)-k]=*p->alcunhas[k];
                        c->plantas[i]->n_alcunhas++;
                    }
                    hasEqual=0;

                }
                //return 1 porque o id já existia:
                return 1;
            }
        }
    }
    //se nao tiver encontrado nenhuma planta com o mesmo ID, proceder à inserção
    if(!hasFound){
        printf("\nolasegundoif\n");

        int k=0;
        //se tipo_ordem for "id":
        //c->tipo_ordem[strlen(c->tipo_ordem)]='\0';
        //if(strcmp(c->tipo_ordem,id)==0){
        if(strcmp(c->tipo_ordem,"id")==0){
            printf("\nolasegundoif2222\n");
            //ver pela ordem do ID
            while(k<tam){
                if(*c->plantas[k]->ID > *p->ID){
                    k++;
                }
                else{
                    break;
                }
            }
        }
        //se tipo_order for "nome"
        //else if(strcmp(c->tipo_ordem,nome)==0){
        else if(strcmp(c->tipo_ordem,"nome")==0){
            //adicionar de acordo com ordem alfabetica de nome cientifico
            while(k<tam){
                if(*c->plantas[k]->nome_cientifico > *p->nome_cientifico){
                    k++;
                }
                else{
                    break;
                }
            }
        }
        //se chegar aqui, é porque alguma coisa deu erro, logo, return -1
        else return -1;

        //copia todos os elementos do vetor uma posicao para a frente
        for(int j=tam-1; j>=k; j--)
        {
            c->plantas[j+1]=c->plantas[j];
        }

        //aloca memoria para adicionar
        *c->plantas[k]->ID = (char)calloc(strlen(p->ID)+1, sizeof(char));
        *c->plantas[k]->nome_cientifico = (char)calloc(strlen(p->nome_cientifico)+1, sizeof(char));
        c->plantas[k]->alcunhas = (char**)calloc((p->n_alcunhas), sizeof(char));
        c->plantas[k]->n_alcunhas = (int)calloc((p->n_alcunhas), sizeof(int));
        c->plantas[k]->n_sementes = (int)calloc((p->n_sementes), sizeof(int));

        //insered dados nas memorias alocadas
        strcpy(c->plantas[k]->ID,p->ID);
        //*c->plantas[k]->ID=*p->ID;
        strcpy(c->plantas[k]->nome_cientifico,p->nome_cientifico);
        //*c->plantas[k]->nome_cientifico=*p->nome_cientifico;
        c->plantas[k]->alcunhas=p->alcunhas;
        c->plantas[k]->n_alcunhas=p->n_alcunhas;
        c->plantas[k]->n_sementes=p->n_sementes;

        (c->tamanho)++;

    }

    return 0;
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
	char *linha,*token,*ID, *nome;
	int n_seeds,n_alcunhas,i,check;
	linha=malloc(300*sizeof(char));
	ID=malloc(10*sizeof(char));
	nome=malloc(MAX_NAME*sizeof(char));
	f=fopen(nome_ficheiro,"r");
	c=colecao_nova(tipo_ordem);

	if(linha==NULL || ID==NULL || nome==NULL || c==NULL ||f==NULL){return NULL;}
	char **alcunhas;
	while(fgets(linha,300,f)!=NULL){
		token=strtok(linha,",");
		strcpy(ID,token);
		
		token=strtok(NULL,",");
		strcpy(nome,token);
		
		token=strtok(NULL,",");
		n_seeds=atoi(token);
		
		token=strtok(NULL,",");
		alcunhas=NULL;
		n_alcunhas=0;
		if(token!=NULL){
			alcunhas=malloc(sizeof(char*));
			if(alcunhas==NULL){return NULL;}
			alcunhas[0]=malloc((strlen(token)+1)*sizeof(char));
			if(alcunhas[0]==NULL){return NULL;}
			strcpy(alcunhas[0],token);
			n_alcunhas++;
			token=strtok(NULL,",");
		}
		while(token!=NULL){
			alcunhas=realloc(alcunhas,(n_alcunhas+1)*sizeof(char*));
			alcunhas[n_alcunhas]=malloc((strlen(token)+1)*sizeof(char));
			if(alcunhas[n_alcunhas]==NULL){return NULL;}
			strcpy(alcunhas[n_alcunhas],token);
			n_alcunhas++;
			token=strtok(NULL,",");
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
	free(p);
	fclose(f);
	free(ID);
	free(nome);
	free(linha);
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

	if(exists==0){free(pos);return NULL;}
	*tam=tamanhov;
	return pos;
}
int colecao_reordena(colecao *c, const char *tipo_ordem)
{
	if(c==NULL){return -1;}
	if(strcmp(c->tipo_ordem,tipo_ordem)==0 || c->tamanho==0){return 0;}

	strcpy(c->tipo_ordem,tipo_ordem);
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
		return 1;
	}
	else{return -1;}
}
