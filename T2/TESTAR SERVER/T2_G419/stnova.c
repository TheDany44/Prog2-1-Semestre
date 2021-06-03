/*****************************************************************/
/*    Estrutura nova a implementar | PROG2 | MIEEC | 2020/21     */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stnova.h"

unsigned long hash(char *str, char* str2, int tamanho);

estrutura *st_nova()
{
    estrutura *tab;
    tab=calloc(1,sizeof(estrutura));
    if(tab==NULL){return NULL;}

    return tab;
}

int recriar_estrutura(estrutura *st,int capacidade){
    if(st==NULL || capacidade<=0){return 0;}

    st->capacidade=capacidade;
    st->estado_celulas=calloc(capacidade,sizeof(int));
    if(st->estado_celulas==NULL){return 0;}
    st->voos=calloc(capacidade,sizeof(elemento_preco*));
    if(st->voos==NULL){free(st->estado_celulas);return 0;}

    return 1;
}


int sondagem_voo(estrutura *st, char* origem,char*destino, int*flag){
    if(st==NULL || origem==NULL || destino==NULL){return -1;}

    int pos,i,newpos;
    pos=hash(origem,destino,st->capacidade);

    for(i=0;i<st->capacidade+1;i++){
        newpos=(pos+i)%st->capacidade;
        if(st->estado_celulas[newpos]==0){
            return newpos;
        }
        if(st->estado_celulas[newpos]==1){
            if(strcmp(st->voos[newpos]->destino,destino) == 0 && strcmp(st->voos[newpos]->origem,origem) == 0){
                *flag=1;
                return newpos;
            }
        }
        
    }
    return -1;
}

int colocar_voo(estrutura *st,aresta_grafo *aresta, char *origem){
    if(st==NULL || aresta==NULL || origem==NULL){
        return 0;
    }
    if(st->capacidade==st->tamanho || st->capacidade==0){return 0;}
    int pos, flag=0;
    pos=sondagem_voo(st,origem,aresta->destino->cidade,&flag);
    if(pos==-1){return 0;}

    elemento_preco *elemento;
    if(flag){
        if(st->voos[pos]->preco>aresta->preco){
            st->voos[pos]->preco=aresta->preco;
            st->voos[pos]->codigo=aresta->codigo;
        }
    }
    else{
        elemento=malloc(sizeof(elemento_preco));
        if(elemento==NULL){return 0;}
        elemento->codigo=aresta->codigo;
        elemento->destino=aresta->destino->cidade;
        elemento->origem=origem;
        elemento->preco=aresta->preco;

        st->voos[pos]=elemento;
        st->estado_celulas[pos]=1;
        st->tamanho++;
    }

    return 1;

}

int st_importa_grafo(estrutura *st, grafo *g)
{
    if(st==NULL || g==NULL){return -1;}

    int tamanho=0,i;

    for(i=0;i<g->tamanho;i++){
        tamanho+=g->nos[i]->tamanho;
    }

    if(!recriar_estrutura(st,tamanho)){return -1;}

    int k;
    no_grafo *no;

    for(i=0;i<g->tamanho;i++){
        no=g->nos[i];

        for(k=0;k<no->tamanho;k++){
            if(!colocar_voo(st,no->arestas[k],no->cidade)){return -1;}
        }

    }

    return 1;
}

int sondagem_procura_voo(estrutura *st, char* origem,char*destino){
    if(st==NULL || origem==NULL || destino==NULL){return -1;}

    int pos,i,newpos;
    pos=hash(origem,destino,st->capacidade);

    for(i=0;i<st->capacidade+1;i++){
        newpos=(pos+i)%st->capacidade;
        if(st->estado_celulas[newpos]==0){
            return -1;
        }
        if(st->estado_celulas[newpos]==1){
            if(strcmp(st->voos[newpos]->destino,destino) == 0 && strcmp(st->voos[newpos]->origem,origem) == 0){
                return newpos;
            }
        }
        
    }
    return -1;
}

char *st_pesquisa(estrutura *st, char *origem, char *destino)
{
    if(st==NULL || origem==NULL || destino==NULL){return NULL;}

    if(st->tamanho<=0){return NULL;}

    int pos;
    pos=sondagem_procura_voo(st,origem,destino);
    if(pos<0){return NULL;}
    
    return st->voos[pos]->codigo;
}

int st_apaga(estrutura *st)
{
    if(st==NULL){return -1;}

    int i;
    for(i=0;i<st->capacidade;i++){
        if(st->estado_celulas[i]==1){
            free(st->voos[i]);
            st->voos[i]=NULL;
        }
    }
    if(st->capacidade!=0){
        free(st->estado_celulas);
        st->estado_celulas=NULL;
        free(st->voos);
        st->voos=NULL;
    }
    free(st);
    st=NULL;
    
    return -1;
}

//------HASH FUNC---------
// HASH djb2 - by dan bernstein
unsigned long hash1(char *str1, int tamanho)
{
    unsigned long hash1 = 5381;
    int c;

    while ((c = *str1++))
        hash1 = ((hash1 << 5) + hash1) + c; /* hash * 33 + c */
    return hash1;
}


unsigned long hash2(const char *chave, int tamanho)
{
    int c, t = strlen(chave);
    unsigned long hash = 7;

    for (c = 0; c < t; c++)
    {
        hash += (int)chave[c];
    }

    return hash;
}

unsigned long hash(char *str1, char *str2, int tamanho){
    return (hash1(str1,tamanho)+hash2(str2,tamanho))%tamanho;
}