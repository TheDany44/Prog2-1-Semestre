#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"
#include <string.h>

void including5strings(char* s,vetor* v){
    int i;
    printf("Introduza 5 strings:\n");
    for (i=0;i<5;i++){
        scanf(" %s",s);
        if (vetor_insere(v,s,-1)==-1){printf("ERRO: A inserir um elemento no vetor\n");exit(1);}
    }

}

void printvetor(vetor* v,char* legenda){
    int i;
    if(vetor_tamanho(v)==-1){printf("ERRO: Tamanho do vetor\n");exit(1);}
    printf("%s: [ ",legenda);
    for (i=0; i<v->tamanho; i++){
        if (i==v->tamanho-1){printf("%s ",v->elementos[i].str);break;}
        printf("%s; ",v->elementos[i].str);

    }
    printf("]\n");

}

int main(){
    int pos;
    char *s;
    vetor* v;
    s=calloc(100,sizeof(char));
    v=vetor_novo();

    if(v==NULL){printf("ERRO: A criar o vetor\n");exit(1);}

    including5strings(s,v);
    if(v->tamanho>4){printf("ERRO: Inseriu mais de 5 elementos!\n");exit(1);}

    char legenda[50]="Vetor Inserido";
    printvetor(v,legenda);
    
    printf("Escreva uma string: ");
    scanf(" %s",s);
    pos=vetor_pesquisa(v,s);
    if (vetor_remove(v,pos)==-1){printf("ERRO: A remover string.\n");exit(1);}
    strcpy(legenda,"Vetor Modificado");
    printvetor(v,legenda);
    
    vetor_ordena(v);
    strcpy(legenda,"Vetor Ordenado");
    printvetor(v,legenda);

    free(v);
    v=NULL;
    free(s);
    s=NULL;
    return 0;
}
