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
    
    char c[]="(";
    elemento = lista_inicio(lst);
    lista* consola;
    consola=lista_nova();
    if(consola==NULL){printf("ERRO!\n");lista_apaga(lst);exit(1);}
    int tamanho_consola;
    tamanho_consola=lista_tamanho(consola);
    int control=0;
    l_elemento* elemento_consola;
    for(i=0;i<tamanho;i++){
        strcpy(game,strstr(elemento->str,c));
        elemento=elemento->proximo;
        elemento_consola=lista_inicio(consola);
        for(a=0;a<tamanho_consola;a++){
            if(strcmp(game,elemento_consola->str)==0){control=1;break;}
            elemento_consola=elemento_consola->proximo;
        }   
        if(!control){
            if(lista_insere(consola,game,NULL)==NULL){printf("ERRO!\n");lista_apaga(lst);lista_apaga(consola);exit(1);}
            tamanho_consola=lista_tamanho(consola);
        }
        control=0;
    }
    if(lista_ordena(consola)==-1){printf("ERRO!\n");lista_apaga(lst);lista_apaga(consola);exit(1);}

    elemento_consola=lista_inicio(consola);
    lista *lst_ord;
    lst_ord=lista_nova();
    if(lst_ord==NULL){printf("ERRO!\n");lista_apaga(lst);lista_apaga(consola);exit(1);}
    for(a=0;a<tamanho_consola;a++){
        lst_sub=lista_pesquisa_substring(lst,elemento_consola->str);
        if(lst_sub==NULL){printf("ERRO!\n");lista_apaga(lst);lista_apaga(consola);lista_apaga(lst_ord);exit(1);}
        if(lista_ordena(lst_sub)==-1){printf("ERRO!\n");lista_apaga(lst);lista_apaga(consola);lista_apaga(lst_ord);exit(1);}
        if(lista_concatena(lst_ord,lst_sub)==NULL){printf("ERRO!\n");lista_apaga(lst);lista_apaga(consola);lista_apaga(lst_ord);exit(1);}
        lista_apaga(lst_sub);
        elemento_consola=elemento_consola->proximo;
    }
    lista_apaga(consola);
    lista_apaga(lst);

    printf("\nLista Ordenada:\n");
    tamanho=lista_tamanho(lst_ord);
    lista_imprime(lst_ord,tamanho);
    
    char gamepos[]="Duke Nukem (PS3)";
    l_elemento* elemento_encontrar;
    elemento=lista_inicio(lst_ord);
    elemento_encontrar=lista_pesquisa(lst_ord,gamepos,LISTA_INICIO);
    for(i=0;i<tamanho;i++){
        if(elemento==elemento_encontrar){break;}
        elemento=elemento->proximo;
    }
    int pos=i;
    printf("\nO jogo %s encontra-se na posição %d.\n",gamepos,pos);

    lista_apaga(lst_ord);
    return 0;
}