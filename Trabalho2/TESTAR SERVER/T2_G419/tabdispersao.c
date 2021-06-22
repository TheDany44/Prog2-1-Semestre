/*****************************************************************/
/*         Tabela de Dispersao | PROG2 | MIEEC | 2020/21         */
/*****************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tabdispersao.h"
#include "grafo.h"

tabela_dispersao *tabela_nova(int capacidade, hash_func *hfunc, sond_func *sfunc)
{
    if(capacidade<=0 || hfunc==NULL || sfunc==NULL){return NULL;}
    //PERGUNTAR PRIMO

    tabela_dispersao* tab;

    tab=(tabela_dispersao*)malloc(sizeof(tabela_dispersao));
    if(tab==NULL){return NULL;}

    tab->hfunc=hfunc;
    tab->sfunc=sfunc;
    tab->capacidade=capacidade;
    tab->tamanho=0;


    tab->estado_celulas=(int*)calloc(tab->capacidade,sizeof(int));
    if(tab->estado_celulas==NULL){free(tab);return NULL;}

    tab->nos=(no_grafo**)calloc(tab->capacidade,sizeof(no_grafo*));
    if(tab->nos==NULL){free(tab);free(tab->estado_celulas);return NULL;}


    return tab;
}

int fazersondagem_add(tabela_dispersao *tab,char* cidade){
    if(tab==NULL || cidade==NULL){return -1;}

    int hash_pos,tentativas=0,s_pos;

    hash_pos=tab->hfunc(cidade,tab->capacidade);

    for(tentativas=0;tentativas<tab->capacidade*tab->capacidade;tentativas++){
        s_pos=tab->sfunc(hash_pos,tentativas,tab->capacidade);

        if(tab->estado_celulas[s_pos]<=0){
            return s_pos;
        }
    }
    return -1;
}


int tabela_adiciona(tabela_dispersao *td, no_grafo *entrada)
{
    if(td==NULL || entrada==NULL){return -1;}

    if(td->capacidade==td->tamanho || td->capacidade<=0){return -1;}
    if(tabela_existe(td,entrada->cidade)!=-1){return -1;}

    int pos;

    pos=fazersondagem_add(td,entrada->cidade);

    td->estado_celulas[pos]=1;
    td->tamanho++;

    td->nos[pos]=entrada;

    return pos;
}

int tabela_remove(tabela_dispersao *td, no_grafo *saida)
{
    if(td==NULL || saida==NULL){return -1;}
    if(td->tamanho<=0){return -1;}

    int pos;
    pos=tabela_existe(td,saida->cidade);
    if(pos==-1){return -1;}

    td->estado_celulas[pos]=-1;

    td->nos[pos]=NULL;

    td->tamanho--;

    return 0;
}

void tabela_apaga(tabela_dispersao *td)
{
    if(td==NULL){return;}

    int i;

    for(i=0;i<td->capacidade;i++){
        if(td->estado_celulas[i]==1){
            td->nos[i]=NULL;
            td->tamanho--;
        }
        td->estado_celulas[i]=-1;
    }
    
    free(td->estado_celulas);
    td->estado_celulas=NULL;
    free(td->nos);
    td->nos=NULL;
    free(td);
    td=NULL;
    return;

}

int tabela_existe(tabela_dispersao *td, const char *cidade)
{
    if(td==NULL || cidade==NULL){return -1;}
    if(td->capacidade==0 || td->tamanho==0){return -1;}
    
    int hash_pos,s_pos;
    unsigned long tentativas=0;

    hash_pos=td->hfunc(cidade,td->capacidade);

    for(tentativas=0;tentativas<td->capacidade*td->capacidade;tentativas++){
        s_pos=td->sfunc(hash_pos,tentativas,td->capacidade);

        if(td->estado_celulas[s_pos]==0){
            return -1;
        }
        if(td->estado_celulas[s_pos]==1){
            if(strcmp(td->nos[s_pos]->cidade,cidade)==0){
                return s_pos;
            }
        }
    }
    return -1;
    
}

tabela_dispersao *tabela_carrega(grafo *g, int tamanho)
{
    if(g==NULL || tamanho<=0){return NULL;}
    if(g->tamanho>tamanho){return NULL;}

    tabela_dispersao *tab;
    tab=tabela_nova(tamanho,hash_krm,sond_rh);
    if(tab==NULL){return NULL;}

    int i;
    for(i=0;i<g->tamanho;i++){
        if(tabela_adiciona(tab,g->nos[i])==-1){
            tabela_apaga(tab);
            return NULL;
        }
    }

    return tab;
}

/*================================================================================*/
unsigned long sond_rh(int pos, int tentativas, int tamanho)
{

    return (pos + tentativas * tentativas) % tamanho;
}

unsigned long hash_krm(const char *chave, int tamanho)
{
    int c, t = strlen(chave);
    unsigned long hash = 7;

    for (c = 0; c < t; c++)
    {
        hash += (int)chave[c];
    }

    return hash % tamanho;
}
