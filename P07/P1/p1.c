#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"



int main(){
    arvore_bst* tree;
    tree=bst_nova();
    if(tree==NULL){return 0;}

    printf("Insira os valores: \n");
    char letra[2];
    while(scanf(" %s",letra)==1){
        if(bst_insere(tree,letra)<0){return 0;}
    }
    printf("***%d altura***\n",bst_altura(tree->raiz));

    printf("Arvore em pré-ordem: ");
    bst_imprime(tree);

    return 0;
}