#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabdispersao.h"



tabela_dispersao* tab_insere_documento(const char *ficheiro, hash_func *hash){
    FILE *f;
    f=fopen(ficheiro,"r");

    tabela_dispersao *tab;
    tab=tabela_nova(100000,hash);
    if(tab==NULL){return NULL;}

    char linha[200], *aux;

    while(fgets(linha,200,f)!=NULL){

        aux=strstr(linha,"\n");
        if(aux!=NULL){
            *aux='\0';
        }

        if(tabela_adiciona(tab,linha,linha)!=0){return NULL;}
    }


    fclose(f);
    return tab;
}

int main(){
    tabela_dispersao *tabdoc;

    tabdoc=tab_insere_documento("englishwords.txt",hash_djbm);
    if(tabdoc==NULL){return 0;}

    mostraTabela(tabdoc);

    if(tabela_alterahash(tabdoc,hash_krm)<1){
        printf("ERRO!\n");
    }

    mostraTabela(tabdoc);

    tabela_apaga(tabdoc);

    return 0;
}