#include <stdio.h>
#include <stdlib.h>

void preenche(int* v,int tamanho){
    int i;
    for(i=0;i<tamanho;i++){
        printf("Introduza o %dº elemento: ",i+1);
        scanf(" %d",v+i);
    }
}

int ordenado(int* v,int tamanho){
    int i,a,controlo=1;
    for(i=tamanho-1;i>=0;i--){
        for(a=0;a<i;a++){
            if(*(v+i)<*(v+a)){
                controlo=0;
                return controlo;
            }
        }
    }
    return controlo;
}

int main(){
    int tamanho;
    printf("Introduza o número de números: ");
    scanf(" %d",&tamanho);
    if(tamanho>100){printf("ERRO: Introduza um maximo de 100 elementos.\n");exit(1);}
    int* v;
    v=malloc(tamanho*sizeof(int));
    if(v==NULL){printf("ERRO: Memória Insuficiente.\n");exit(1);}
    preenche(v,tamanho);

    if(ordenado(v,tamanho)){
        printf("O vetor está ordenado!\n");
        printf("Elementos do vetor por ordem decrescente:\n");
        printf("{");
        int i;
        for(i=tamanho-1;i>0;i--){
            printf("%d,",*(v+i));
        }
        printf("%d}\n",*v);

    }
    else{printf("O vetor não está ordenado!\n");}

    free(v);
    v=NULL;
    return 0;
}