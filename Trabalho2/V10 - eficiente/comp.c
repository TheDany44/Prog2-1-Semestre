#include <stdio.h>
#include <time.h>
#include <string.h>

int main(){
    clock_t start, end;
    int i,h=0;

    start=clock();
    for(i=0;i<1000000;i++){
        if(329==329){
            h++;
        }
    }
    end=clock();

    printf("\tTempo a comparar %d numeros: %.8f\n\n\n",h, (double)(end - start) / CLOCKS_PER_SEC);

    char s1[]="compararcompararcompararcomprar lol",s2[]="compararcompararcompararcomprar lol";
    h=0;

    start=clock();
    for(i=0;i<21;i++){
        if(strcmp(s1,s2)==0){
            h++;
        }
    }
    end=clock();

    printf("\tTempo a comparar %d strings: %.8f\n\n\n",h, (double)(end - start) / CLOCKS_PER_SEC);

}