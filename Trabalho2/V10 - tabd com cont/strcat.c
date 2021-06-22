#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char frase[]="EU SOU GAY", frase2[]="mentira";
    char *str1, *str2;
    char *teste1, *teste2;

    str1=malloc((strlen(frase)+1)*sizeof(char));
    str2=malloc((strlen(frase2)+1)*sizeof(char));

    strcpy(str1,frase);
    strcpy(str2,frase2);

    teste1=str1;
    teste2=str2;

    strcat(teste1,teste2);

    printf("%s\n",teste1);
    printf("------------------------------\n%s\n",str1);

    free(str1);
    free(str2);
}