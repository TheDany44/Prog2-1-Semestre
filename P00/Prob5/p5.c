#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inverte(char *strOriginal, char *strInvertida){
    int i,a=0;
    for(i=strlen(strOriginal)-1;i>=0;i--){
        strInvertida[a]=strOriginal[i];
        a++;
    }
    strInvertida[a]='\0';
}

int main(){
    char palavra[100],palavrainvertida[100];
    while(1){ 
        printf("Palavra: ");
        scanf(" %s",palavra);
        inverte(palavra,palavrainvertida);
        printf("Resultado: ");
        if(strcmp(palavra,palavrainvertida)==0){
            printf("%s é capicua.\n",palavra);
        }
        else{
            printf("%s não é capicua.\n",palavra);
        }
    }
    return 0;
}