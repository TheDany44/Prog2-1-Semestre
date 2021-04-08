#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convert(char* binary,char *octal){
    int aux,resto,i=0;
    aux=atoi(octal);

    while(aux!=0){
        resto=aux%2;
        
    }
}

int main(){
    char message[101],octal[10],*binary;
    int tamanho,i;
    
    fgets(message,100,stdin);
    tamanho=strlen(message);

    if(tamanho<=0 || tamanho>100){exit(1);}

    binary=malloc(8);
    for(i=0;i<tamanho;i++){
        sprintf(octal,"%o",message[i]);
        convert(binary,octal);
    }


    return 0;
}