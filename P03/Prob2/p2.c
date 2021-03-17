#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"
#include "lista.h"
#include <time.h>

int main(){
    clock_t start_t, end_t;
    FILE *f;
    f=fopen("nomes.txt","r");
    srand(time(0));
    char nome[100];
    int aleatorio,i,tamanho;
    start_t=clock();


    vetor *v;
    v=vetor_novo();
    while(fgets(nome,100,f)!=NULL){
        vetor_insere(v,nome,0);
    }
    fclose(f);
    tamanho=vetor_tamanho(v);
    for(i=0;i<10000;i++){ 
        aleatorio=rand()%tamanho;
        if(vetor_elemento(v,aleatorio)==NULL){printf("ERRO!");}
    }
    for (i=0;i<tamanho;i++){
        vetor_remove(v,0);
    }
    f=fopen("nomes.txt","r");
    while(fgets(nome,100,f)!=NULL){
        vetor_insere(v,nome,-1);
    }

    
    end_t=clock();
    fclose(f);
    printf("Tempo para vetor: %.3f\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    f=fopen("nomes.txt","r");
    start_t=clock();

    lista* lst;
    lst=lista_nova();
    l_elemento* el;
    el = lista_inicio(lst);
    while (fgets(nome,100,f)!=NULL){
        lista_insere(lst,nome,el);
    }
    fclose(f);
    tamanho=lista_tamanho(lst);
    for(i=0;i<10000;i++){
        aleatorio=rand()%tamanho;
        if(lista_elemento(lst,aleatorio)==NULL){printf("ERRO!");}
    }
    for(i=0;i<tamanho;i++){
        lista_remove(lst,0);
    }
    fopen("nomes.txt","r");
    while(fgets(nome,100,f)!=NULL){
        lista_insere(lst,nome,NULL);
    }


    end_t=clock();
    printf("Tempo para lista: %.3f\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    fclose(f);
    vetor_apaga(v);
    lista_apaga(lst);
    return 0;
}