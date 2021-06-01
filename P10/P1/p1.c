#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include <time.h>
#include "tabdispersao.h"


lista *lista_insere_documento(const char *ficheiro){
    FILE *f;
    f=fopen(ficheiro,"r");

    lista *lst;
    lst=lista_nova();
    if(lst==NULL){return NULL;}

    char linha[200], *aux;

    while(fgets(linha,200,f)!=NULL){

        aux=strstr(linha,"\n");
        if(aux!=NULL){
            *aux='\0';
        }

        if(lista_insere(lst,linha,NULL)==NULL){return NULL;}
    }

    fclose(f);
    return lst;
}

tabela_dispersao* tab_insere_documento(const char *ficheiro, hash_func *hash){
    FILE *f;
    f=fopen(ficheiro,"r");

    tabela_dispersao *tab;
    tab=tabela_nova(100000,hash);
    if(tab==NULL){return NULL;}

    char linha[200], *aux;

    while(fgets(linha,200,f)!=NULL){

        aux=strstr(linha,"\n");
        if(aux!=NULL){
            *aux='\0';
        }

        if(tabela_adiciona(tab,linha,linha)!=0){return NULL;}
    }


    fclose(f);
    return tab;
}

lista* randomlst(tabela_dispersao *tab){
    srand(time(NULL));
    int i,r;

    objeto* vetor;
    vetor=tabela_elementos(tab,&i);
    int num=i;
    if(vetor==NULL){return NULL;}
    
    lista* lst;
    lst=lista_nova();
    if(lst==NULL){return NULL;}

    for(i=0;i<500;i++){
        r=rand()%100000;
        if(lista_insere(lst,vetor[i].valor,NULL)==NULL){return NULL;}    
    }

    free(vetor); 


    return lst;
}

int lista_procura(lista* lstdoc,lista* lstfind){
    l_elemento* elem;
    for(elem=lstfind->inicio;elem==NULL;elem=elem->proximo){

        if(lista_pesquisa(lstdoc,elem->str,LISTA_INICIO)==NULL){
            return 0;
        }
    }
    return 1;
}

int tab_procura(tabela_dispersao* tabdoc,lista* lstfind){
    l_elemento* elem;
    for(elem=lstfind->inicio;elem==NULL;elem=elem->proximo){
        
        if(tabela_valor(tabdoc,elem->str)==NULL){return 0;}
    }
    return 1;
    
}

double teste(hash_func *hash){
    
    //1.1
    lista *lstdoc;

    __clock_t inicio,fim;
    double tempolst, tempotab, tabtotal;
    inicio=clock();
    
    lstdoc=lista_insere_documento("englishwords.txt");
    if(lstdoc==NULL){return 0;}

    fim=clock();
    tempolst=(double)(fim-inicio)/CLOCKS_PER_SEC;
    printf("Tempo em segundos da lista a inserir é: %lf\n",tempolst);

    tabela_dispersao *tabdoc;

    inicio=clock();

    tabdoc=tab_insere_documento("englishwords.txt",hash);
    if(tabdoc==NULL){lista_apaga(lstdoc);return 0;}

    fim=clock();
    tempotab=(double)(fim-inicio)/CLOCKS_PER_SEC;
    printf("Tempo em segundos da tabela a inserir é: %lf\n",tempotab);

    if(hash_krm==hash){mostraTabela(tabdoc);}

    if(tempotab>tempolst){
        printf("\n***A tabela é mais lenta a inserir %lf segundos***\n\n",tempotab-tempolst);
    }
    else{
        printf("\n***A lista é mais lenta a inserir %lf segundos***\n\n",tempolst-tempotab);
    }
    tabtotal=tempotab;

    //1.2
    lista *lstele;
    lstele=randomlst(tabdoc);

    inicio=clock();
    
    if(lista_procura(lstdoc,lstele)==0){return 0;}

    fim=clock();
    tempolst=(double)(fim-inicio)/CLOCKS_PER_SEC;
    printf("Tempo em segundos da lista a pesquisar é: %lf\n",tempolst);


    inicio=clock();

    if(tab_procura(tabdoc,lstele)==0){return 0;}

    fim=clock();
    tempotab=(double)(fim-inicio)/CLOCKS_PER_SEC;
    printf("Tempo em segundos da tabela a pesquisar é: %lf\n",tempotab);

    if(tempotab>tempolst){
        printf("\n***A tabela é mais lenta a pesquisar %lf segundos***\n\n",tempotab-tempolst);
    }
    else{
        printf("\n***A lista é mais lenta a pesquisar %lf segundos***\n\n",tempolst-tempotab);
    }

    tabtotal+=tempotab;
    lista_apaga(lstele);
    lista_apaga(lstdoc);
    tabela_apaga(tabdoc);
    return tabtotal;
}

int main(){
    printf("-----Teste da hash djbm-----\n");
    printf("-----A hash djbm demora %lf segundos no total-----\n ",teste(hash_djbm));
    printf("\n\n-----Teste da hash krm-----\n");
    printf("-----A hash krm demora %lf segundos no total-----\n ",teste(hash_krm));
    return 0;
}