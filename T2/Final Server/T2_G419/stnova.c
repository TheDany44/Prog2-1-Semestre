/*****************************************************************/
/*    Estrutura nova a implementar | PROG2 | MIEEC | 2020/21     */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stnova.h"

#define RAIZ (1)
#define PAI(x) (x / 2)
#define FILHO_ESQ(x) (x * 2)
#define FILHO_DIR(x) (x * 2 + 1)

estrutura *st_nova()
{
    estrutura *tab_origem;
    tab_origem=calloc(1,sizeof(estrutura));
    if(tab_origem==NULL){return NULL;}

    return tab_origem;
}

int recriar_estrutura(estrutura *st,int capacidade){
    if(st==NULL || capacidade<=0){return 0;}

    st->capacidade=capacidade;
    st->estado_celulas=calloc(capacidade,sizeof(int));
    if(st->estado_celulas==NULL){return 0;}
    st->destab=calloc(capacidade,sizeof(tab_destino*));
    if(st->destab==NULL){free(st->estado_celulas);return 0;}

    return 1;
}

int sondagem_fazer_origem(estrutura *st, char* cidade){
    if(st==NULL || cidade==NULL){return -1;}

    int pos,i,newpos;
    pos=hash_krm(cidade,st->capacidade);

    for(i=0;i<st->capacidade;i++){
        newpos=(pos+i)%st->capacidade;
        if(st->estado_celulas[newpos]==0){
            return newpos;
        }
    }
    return -1;
}

tab_destino *newtab_d(int capacidade,char *cidade){
    if(capacidade<0){return NULL;}

    tab_destino *tab;
    tab=calloc(1,sizeof(tab_destino));
    if(tab==NULL){return NULL;}

    tab->orig=malloc((strlen(cidade)+1)*sizeof(char));
    if(tab->orig==NULL){free(tab);return NULL;}
    strcpy(tab->orig,cidade);
    tab->capacidade=capacidade;
    tab->heap_p=calloc(capacidade,sizeof(heap_preco*));
    if(tab->heap_p==NULL){free(tab->orig);free(tab);return NULL;}
    tab->estado_celulas=calloc(capacidade,sizeof(int));
    if(tab->estado_celulas==NULL){free(tab->orig);free(tab->heap_p),free(tab);return NULL;}
    return tab;
}

tab_destino *colocar_origem(estrutura *st,no_grafo *no){
    if(st == NULL || no == NULL){return NULL;}
    if(st->tamanho>=st->capacidade){return NULL;}

    int pos;
    pos=sondagem_fazer_origem(st,no->cidade);
    if(pos<0){return NULL;}

    tab_destino *tab_dest;
    tab_dest=newtab_d(no->tamanho,no->cidade);
    if(tab_dest==NULL){return NULL;}

    st->destab[pos]=tab_dest;
    st->estado_celulas[pos]=1;
    st->tamanho++;

    return tab_dest;
}

int sondagem_fazer_destino(tab_destino *tab, char* cidade){
    if(tab==NULL || cidade==NULL){return -1;}

    int pos,i,newpos;
    pos=hash_krm(cidade,tab->capacidade);

    for(i=0;i<tab->capacidade;i++){
        newpos=(pos+i)%tab->capacidade;
        if(tab->estado_celulas[newpos]==1){
            if(strcmp(tab->heap_p[newpos]->dest,cidade)==0){
                return newpos;
            }
        }
        if(tab->estado_celulas[newpos]==0){
            return newpos;
        }
    }
    return -1;
}

heap_preco *heap_pnova(char *destino){
    if(destino==NULL){return NULL;}

    heap_preco *h;
    h=calloc(1,sizeof(heap_preco));
    if(h==NULL){return NULL;}

    h->dest=malloc((strlen(destino)+1)*sizeof(char));
    if(h->dest==NULL){free(h);return NULL;}
    strcpy(h->dest,destino);

    return h;
}

elemento_preco *elemento_pnovo(int preco, char* codigo){
    if(preco<0 || codigo == NULL){return NULL;}

    elemento_preco *elemento;
    elemento=malloc(sizeof(elemento_preco));
    if(elemento==NULL){return NULL;}

    elemento->codigo=malloc((strlen(codigo)+1)*sizeof(char));
    if(elemento->codigo==NULL){free(elemento);return NULL;}
    strcpy(elemento->codigo,codigo);

    elemento->preco=preco;

    return elemento;
}

int menor_quep(elemento_preco *e1, elemento_preco *e2)
{
    if (e1 == NULL || e2 == NULL)
    {
        return 0;
    }

    return e1->preco < e2->preco;
}

int heap_pinsere(heap_preco *h,aresta_grafo *aresta){
    if(h==NULL || aresta==NULL){return 0;}

    elemento_preco *aux = NULL, *elem;
    int i = 0;

    h->tamanho++;
    h->elementos=realloc(h->elementos,(h->tamanho+1)*sizeof(elemento_preco*));
    if(h->elementos==NULL){return 0;}

    elem = elemento_pnovo(aresta->preco,aresta->codigo);

    /* coloca elemento no fim da heap */
    i = h->tamanho;
    h->elementos[i] = elem;

    /* enquanto elemento for mais prioritario do que o respetivo pai, troca-os */
    while (i != RAIZ && menor_quep(h->elementos[i], h->elementos[PAI(i)]))
    {
        aux = h->elementos[PAI(i)];
        h->elementos[PAI(i)] = h->elementos[i];
        h->elementos[i] = aux;
        i = PAI(i);
    }
    return 1;
}

int colocar_voo(tab_destino *tab_dest,aresta_grafo *aresta){
    if(tab_dest==NULL || aresta==NULL){
        return 0;
    }

    if(tab_dest->tamanho>=tab_dest->capacidade){
        return 0;
    }

    int pos;
    pos=sondagem_fazer_destino(tab_dest,aresta->destino->cidade);
    if(pos<0){return 0;}

    heap_preco *h;
    if(tab_dest->estado_celulas[pos]==0){
        h=heap_pnova(aresta->destino->cidade);
    }
    else{
        h=tab_dest->heap_p[pos];
    }
    if(!heap_pinsere(h,aresta)){return 0;}

    if(tab_dest->estado_celulas[pos]==0){
        tab_dest->heap_p[pos]=h;
        tab_dest->estado_celulas[pos]=1;
        tab_dest->tamanho++;
    }

    return 1;

}

int st_importa_grafo(estrutura *st, grafo *g)
{
    if(st==NULL || g==NULL){return -1;}

    if(!recriar_estrutura(st,g->tamanho)){return -1;}

    int i, k;
    no_grafo *no;
    aresta_grafo *a;
    tab_destino *tab_dest;

    for(i=0;i<g->tamanho;i++){  //viaja por todos os nos
        no=g->nos[i];
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

    int pos,i,newpos;
    pos=hash_krm(cidade,st->capacidade);

    for(i=0;i<st->capacidade;i++){
        newpos=(pos+i)%st->capacidade;
        if(st->estado_celulas[newpos]==1){
            if(strcmp(st->destab[newpos]->orig,cidade)==0){
                return newpos;
            }
        }
        if(st->estado_celulas[newpos]==0){
            return -1;
        }
    }
    return -1;
}

int sondagem_procura_destino(tab_destino *tab, char* cidade){
    if(tab==NULL || cidade==NULL){return -1;}

    int pos,i,newpos;
    pos=hash_krm(cidade,tab->capacidade);

    for(i=0;i<tab->capacidade;i++){
        newpos=(pos+i)%tab->capacidade;
        if(tab->estado_celulas[newpos]==1){
            if(strcmp(tab->heap_p[newpos]->dest,cidade)==0){
                return newpos;
            }
        }
        if(tab->estado_celulas[newpos]==0){
            return -1;
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

    /*char* encontrado,*copiar;
    copiar=tab_dest->heap_p[pos]->elementos[RAIZ]->codigo;
    encontrado=malloc((strlen(copiar)+1)*sizeof(char));
    strcpy(encontrado,copiar);
    return encontrado;*/
    return tab_dest->heap_p[pos]->elementos[RAIZ]->codigo;
}

int heap_papaga(heap_preco *h){
    if(h==NULL){return 0;}

    int i;
    for(i=RAIZ;i<=h->tamanho;i++){
        free(h->elementos[i]->codigo);
        h->elementos[i]->codigo=NULL;
        free(h->elementos[i]);
        h->elementos[i]=NULL;
    }
    if(h->tamanho!=0){
        free(h->elementos);
    }
    free(h->dest);
    h->dest=NULL;
    free(h);
    h=NULL;
    return 1;

}

int tab_dapaga(tab_destino *tab){
    if(tab==NULL){return 0;}

    int i;
    for(i=0;i<tab->capacidade;i++){
        if(tab->estado_celulas[i]==1){
            if(!heap_papaga(tab->heap_p[i])){return 0;}
        }
    }
    
    free(tab->estado_celulas);
    tab->estado_celulas=NULL;
    free(tab->heap_p);
    tab->heap_p=NULL;
    free(tab->orig);
    tab->orig=NULL;
    free(tab);
    tab=NULL;
    return 1;
}

int st_apaga(estrutura *st)
{
    if(st==NULL){return -1;}

    int i;
    for(i=0;i<st->capacidade;i++){
        if(st->estado_celulas[i]==1){
            if(!tab_dapaga(st->destab[i])){return -1;}
        }
    }
    if(st->capacidade!=0){
        free(st->estado_celulas);
        st->estado_celulas=NULL;
        free(st->destab);
        st->destab=NULL;
    }
    free(st);
    st=NULL;
    
    return -1;
}

//------HASH FUNC---------
unsigned long hash(const char *chave, int tamanho)
{
    int c, t = strlen(chave);
    unsigned long hash = 7;

    for (c = 0; c < t; c++)
    {
        hash += (int)chave[c];
    }

    return hash % tamanho;
}

//-------PROBE FUNC-------
unsigned long sond_linear(int pos, int tentativas, int tamanho){

    return (pos + tentativas) % tamanho;
}