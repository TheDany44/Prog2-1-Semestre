#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "plantas.h"
#include <time.h>

int main(){ 

    colecao *c;
    planta *pr;
    c=colecao_importa("db_small.txt","id");


    int i;
    printf("%s\n",c->plantas[337]->ID);
    for(i=0;i<c->plantas[337]->n_alcunhas;i++){
        printf("%s",c->plantas[337]->alcunhas[i]);
    }
}