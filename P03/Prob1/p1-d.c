#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include <string.h>

int main(){
    FILE *f;
    f=fopen("arquivo.txt","r");
    char game[150],ps2[]="PS2";
    lista* lst;
    l_elemento* elemento;
    int tamanho,i,tamanho_sub, a;
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
    lista_imprime(lst,tamanho);

    lista* lst_sub;
    l_elemento *elemento_sub, *elemento_remover;
    lst_sub=lista_pesquisa_substring(lst,ps2);
    if (lst_sub==NULL){printf("ERRO!\n");lista_apaga(lst_sub);lista_apaga(lst);exit(1);}
    tamanho_sub=lista_tamanho(lst_sub);
    if(tamanho==0){printf("Não foi encontrada essa substring.\n");}
    else{
        elemento_sub=lista_inicio(lst_sub);
        for(i=0;i<tamanho_sub;i++){
            elemento_remover=lista_pesquisa(lst,elemento_sub->str,LISTA_INICIO);
            if(lista_remove(lst,elemento_remover)==NULL){printf("ERRO!\n");lista_apaga(lst_sub);lista_apaga(lst);exit(1);}
            elemento_sub=elemento_sub->proximo;
        }
    }
    lista_apaga(lst_sub);
    tamanho=lista_tamanho(lst);
    printf("\nApós a remoção de jogos PS2 a lista tem %d jogos\n",tamanho);
    f=fopen("jogos2.txt","w");
    elemento=lista_inicio(lst);
    for(i=0;i<tamanho;i++){
        strcpy(game,elemento->str);
        a=strlen(game);
        game[a]='\n';
        game[a+1]='\0';
        fputs(game,f);
        elemento=elemento->proximo;
    }
    fclose(f);
    

    f=fopen("oldies.txt","r");
    lista *lstold;
    lstold = lista_nova();
    if(lstold==NULL){printf("ERRO!\n");lista_apaga(lst);exit(1);}
    while(fgets(game,150,f)!=NULL){
        game[strlen(game)-1]='\0';
        if(lista_insere(lstold,game,NULL)==NULL){printf("ERRO!\n");lista_apaga(lst);lista_apaga(lstold);exit(1);}
    }
    fclose(f);
    tamanho=lista_tamanho(lstold);
    printf("\nForam carregados %d jogos antigos:\n",tamanho);
    
    lista_imprime(lstold,tamanho);
    if(lista_concatena(lst,lstold)==NULL){printf("ERRO!\n");lista_apaga(lst);lista_apaga(lstold);exit(1);}
    
    lista_apaga(lstold);
    tamanho=lista_tamanho(lst);
    printf("\nApós a concatenação a lista final contem %d jogos:\n",tamanho);
    lista_imprime(lst,tamanho);
    




    lista_apaga(lst);
    return 0;
}