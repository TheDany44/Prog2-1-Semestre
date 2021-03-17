#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include <string.h>

int main(){
    FILE *f;
    f=fopen("arquivo.txt","r");
    char game[150];
    lista* lst;
    l_elemento* elemento;
    int tamanho,i;
    lst=lista_nova();
    if(lst==NULL){printf("ERRO!\n");exit(1);}
    while (fgets(game,150,f)!=NULL){
        game[strlen(game)-1]='\0';
        elemento=lista_insere(lst,game,NULL);
        if(elemento==NULL){printf("ERRO!\n");lista_apaga(lst);exit(1);}
    }
    fclose(f);
    tamanho=lista_tamanho(lst);
    if(tamanho==-1){printf("ERRO!\n");lista_apaga(lst);exit(1);}
    printf("Foram carregados %d jogos.\n",tamanho);
    elemento=lista_inicio(lst);
    if(elemento==NULL){printf("ERRO!");lista_apaga(lst);exit(1);}
    for (i=0;i<tamanho;i++){
        printf("Pos %d -> %s\n",i,elemento->str);
        elemento=elemento->proximo;
    }


    lista_apaga(lst);
    return 0;
}