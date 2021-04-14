#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"
#include <string.h>

void imprimir(vetor* vet){

    if(vet==NULL){exit(1);}
    int i, tam;
    tam=vetor_tamanho(vet);

    for(i=0; i<tam;i++){
        printf("O elemento %d é %s\n",i+1,vet->elementos[i].str);
    }
}




int main(){

    int i,pos;
    char s1[200];
    vetor* vet;
    vet=vetor_novo();


    printf("Inserir 5 strings: ");

    for(i=0; i<5;i++){
        scanf("%s",s1);
        //fgets(s1,200,stdin);
        //s1[strlen(s1)-1]='\0';
        vetor_insere(vet,s1,-1);
    }

    imprimir(vet);
    
    printf("Insira nova string: ");
    scanf("%s",s1);

    pos=vetor_pesquisa(vet, s1);

    if(pos!=-1){
        vetor_remove(vet,pos);
        printf("String removida\n");
        
    }
    else
        printf("String nao removida\n");

    imprimir(vet);
    vetor_ordena(vet);
    imprimir(vet);

    printf("Insira nova string: ");
    scanf("%s",s1);

    vetor_atribui(vet,1,s1);
    imprimir(vet);


    vetor_apaga(vet);

    return 0;
}