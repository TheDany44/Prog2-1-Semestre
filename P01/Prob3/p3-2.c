#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    FILE *f;
    char linha[200],*token,*link;
    const char beg[9]="<a href\"", endlink[2]="\"";

    f=fopen("pagina.html","r");
    while (fgets(linha,200,f)){
        if (strstr(linha,beg)==NULL){continue;}
        token = strtok(strstr(linha,beg),endlink);
        token = strtok(NULL,endlink);
        link = token;
        printf("%s\n",token);

    }

    fclose(f);
    return 0;
}