#include <stdlib.h>
#include <stdio.h>


int main(){
    int tamanho,i;

    printf("Número de elementos: ");
    scanf(" %d",&tamanho);
    
    int *v;
    v=calloc(tamanho,sizeof(int));
    if (v==NULL){printf("ERRO! Memória cheia!\n");}
    
    for (i=0;i<tamanho;i++){
        printf("Introduza o %dº elemento: ",i+1);
        scanf(" %d",v+i);
    }
    printf("\nVetror Original: [ ");
    for (i=0;i<tamanho;i++){
        printf("%d ",*(v+i));
    }
    printf("]\n");

    printf("Numeros pares: [ ");

    for (i=0;i<tamanho;i++){
        if (*(v+i)%2==0)
            printf("%d ",*(v+i));

    }
    printf("]\n");

    printf("Numeros impares: [ ");

    for(i=0;i<tamanho;i++){
        if(*(v+i)%2!=0)
            printf("%d ", *(v+i));
    }
    printf("]\n");
    free(v);
    v=NULL;

    return 0;
}