/*****************************************************************/
/*    Estrutura nova a implementar | PROG2 | MIEEC | 2020/21     */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stnova.h"

int tab_dapaga(tab_destino *tab);

unsigned long hash(char *str);

int primo(int num){
    int i;
    for(i=2;i<=num/2;i++){
        if(num%i==0){
            return primo(num+1);
        }
    }
    return num;
}

estrutura *st_nova()
{
    estrutura *tab_origem;
    tab_origem=(estrutura*)calloc(1,sizeof(estrutura));
    if(tab_origem==NULL){return NULL;}

    return tab_origem;
}

int recriar_estrutura(estrutura *st,int capacidade){
    if(st==NULL || capacidade<=0){return 0;}
    capacidade=primo(capacidade+1);
    st->capacidade=capacidade;
    st->estado_orig=(char**)calloc(capacidade,sizeof(char*));
    if(st->estado_orig==NULL){return 0;}
    st->destab=(tab_destino**)calloc(capacidade,sizeof(tab_destino*));
    if(st->destab==NULL){free(st->estado_orig);return 0;}

    return 1;
}

int sondagem_fazer_origem(estrutura *st, char* cidade){
    if(st==NULL || cidade==NULL){return -1;}

    int i,newpos;
    unsigned long pos;
    pos=hash(cidade);

    for(i=0;i<st->capacidade;i++){
        newpos=(pos+i)%st->capacidade;
        if(st->estado_orig[newpos]==NULL){
            return newpos;
        }
    }
    return -1;
}

tab_destino *newtab_d(int capacidade){
    if(capacidade<0){return NULL;}

    tab_destino *tab;
    tab=(tab_destino*)calloc(1,sizeof(tab_destino));
    if(tab==NULL){return NULL;}

    capacidade=primo(capacidade+1);
    tab->capacidade=capacidade;
    tab->elem=(elemento_preco**)calloc(capacidade,sizeof(elemento_preco*));
    if(tab->elem==NULL){free(tab);return NULL;}
    tab->estado_dest=(char**)calloc(capacidade,sizeof(char*));
    if(tab->estado_dest==NULL){free(tab->elem),free(tab);return NULL;}
    return tab;
}

tab_destino *colocar_origem(estrutura *st,no_grafo *no){
    if(st == NULL || no == NULL){return NULL;}
    if(st->tamanho>=st->capacidade){return NULL;}

    int pos;
    pos=sondagem_fazer_origem(st,no->cidade);
    if(pos<0){return NULL;}

    tab_destino *tab_dest;
    tab_dest=newtab_d(no->tamanho*2);
    if(tab_dest==NULL){return NULL;}

    st->destab[pos]=tab_dest;
    st->estado_orig[pos]=no->cidade;
    st->tamanho++;

    return tab_dest;
}

int sondagem_fazer_destino(tab_destino *tab, char* cidade,int *flag){
    if(tab==NULL || cidade==NULL){return -1;}

    int i,newpos;
    unsigned long pos;
    pos=hash(cidade);

    for(i=0;i<tab->capacidade;i++){
        newpos=(pos+i)%tab->capacidade;
        if(tab->estado_dest[newpos]==NULL){
            *flag=1;
            return newpos;
        }
        if(strcmp(tab->estado_dest[newpos],cidade)==0){
            return newpos;
        }
        
    }
    return -1;
}

elemento_preco *elemento_pnovo(){

    elemento_preco *elemento;
    elemento=(elemento_preco*)malloc(sizeof(elemento_preco));
    if(elemento==NULL){return NULL;}

    return elemento;
}

int colocar_voo(tab_destino *tab_dest,aresta_grafo *aresta){
    if(tab_dest==NULL || aresta==NULL){
        return 0;
    }

    if(tab_dest->tamanho>=tab_dest->capacidade){
        return 0;
    }

    int pos,flag=0;
    pos=sondagem_fazer_destino(tab_dest,aresta->destino->cidade,&flag);
    if(pos<0){return 0;}

    elemento_preco *epreco;
    if(flag){
        epreco=elemento_pnovo();
        if(epreco==NULL){return 0;}
        tab_dest->elem[pos]=epreco;
        tab_dest->estado_dest[pos]=aresta->destino->cidade;
        tab_dest->tamanho++;
        epreco->codigo=aresta->codigo;
        epreco->preco=aresta->preco;
    }
    else if(tab_dest->elem[pos]->preco>aresta->preco){
        tab_dest->elem[pos]->preco = aresta->preco;
        tab_dest->elem[pos]->codigo = aresta->codigo;
    }

    return 1;

}

int st_importa_grafo(estrutura *st, grafo *g)
{
    if(st==NULL || g==NULL){return -1;}

    if(!recriar_estrutura(st,g->tamanho*2)){return -1;}

    int i, k;
    no_grafo *no;
    aresta_grafo *a;
    tab_destino *tab_dest;

    for(i=0;i<g->tamanho;i++){  //viaja por todos os nos
        no=g->nos[i];
        if(no->tamanho==0){continue;}
        tab_dest=colocar_origem(st,no);
        if(tab_dest==NULL){return -1;}

        for(k=0;k<no->tamanho;k++){   //viaja por todas as arestas
            a=no->arestas[k];
            if(!colocar_voo(tab_dest,a)){return -1;}

        }
    }  

    return 1;
}

int sondagem_procura_origem(estrutura *st, char* cidade){
    if(st==NULL || cidade==NULL){return -1;}

    int i,newpos;
    unsigned long pos;
    pos=hash(cidade);

    for(i=0;i<st->capacidade;i++){
        newpos=(pos+i)%st->capacidade;
        if(st->estado_orig[newpos]==NULL){
            return -1;
        }
        if(strcmp(st->estado_orig[newpos],cidade)==0){
            return newpos;
        }
        
    }
    return -1;
}

int sondagem_procura_destino(tab_destino *tab, char* cidade){
    if(tab==NULL || cidade==NULL){return -1;}

    int i,newpos;
    unsigned long pos;
    pos=hash(cidade);

    for(i=0;i<tab->capacidade;i++){
        newpos=(pos+i)%tab->capacidade;
        if(tab->estado_dest[newpos]==NULL){
            return -1;
        }
        if(strcmp(tab->estado_dest[newpos],cidade)==0){
            return newpos;
        }
        
    }
    return -1;
}


char *st_pesquisa(estrutura *st, char *origem, char *destino)
{
    if(st==NULL || origem==NULL || destino==NULL){return NULL;}

    if(st->tamanho<=0){return NULL;}

    int pos;
    pos=sondagem_procura_origem(st,origem);
    if(pos<0){return NULL;}

    tab_destino *tab_dest;
    tab_dest=st->destab[pos];
    if(tab_dest->tamanho<=0){return NULL;}

    pos=sondagem_procura_destino(tab_dest,destino);
    if(pos<0){return NULL;}

    return tab_dest->elem[pos]->codigo;
}

int tab_dapaga(tab_destino *tab){
    if(tab==NULL){return 0;}

    int i;
    for(i=0;i<tab->capacidade;i++){
        if(tab->estado_dest[i]!=NULL){
            free(tab->elem[i]);
            tab->elem[i]=NULL;
            
        }
    }
    free(tab->estado_dest);
    tab->estado_dest=NULL;
    free(tab->elem);
    tab->elem=NULL;
    free(tab);
    tab=NULL;
    return 1;
}

int st_apaga(estrutura *st)
{
    if(st==NULL){return -1;}

    int i;
    for(i=0;i<st->capacidade;i++){
        if(st->estado_orig[i]!=NULL){
            if(!tab_dapaga(st->destab[i])){return -1;}
    
        }
    }
    if(st->capacidade!=0){
        free(st->estado_orig);
        st->estado_orig=NULL;
        free(st->destab);
        st->destab=NULL;
    }
    free(st);
    st=NULL;
    
    return -1;
}


//------HASH FUNC---------
// HASH djb2 - by dan bernstein
unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}



/*unsigned long hash(const char *chave, int tamanho)
{
    int c, t = strlen(chave);
    unsigned long hash = 7;

    for (c = 0; c < t; c++)
    {
        hash += (int)chave[c];
    }

    return hash % tamanho;
}*/