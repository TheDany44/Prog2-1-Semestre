#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char *frase, sep[]=" ",*token,*palavramaior;
    frase=malloc(200*sizeof(char));
    palavramaior=malloc(50*sizeof(char));
    int a=0,num,max=-1,sum=0;

    printf("Frase? ");
    fgets(frase,200,stdin);
    frase[strlen(frase)-1]='\0';

    token=strtok(frase,sep);
    while(token!=NULL){
        a++;
        num=strlen(token);
        if (max<num){
            palavramaior=realloc(palavramaior,strlen(token)+1);
            strcpy(palavramaior,token);
        }
        sum+=num;
        token=strtok(NULL,sep);
    }
    printf("Número de palavras: %d\n",a);
    printf("Palavra maior: %s\n",palavramaior);
    printf("Comprimento médio: %.1f\n",(float)sum/a);

    free(palavramaior);
    palavramaior=NULL;
    free(frase);
    frase=NULL;
    return 0;
}