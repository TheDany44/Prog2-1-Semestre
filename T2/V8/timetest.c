#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct tm data;

int main(){
    data tempo,tempo2;
    tempo.tm_hour=0;
    tempo.tm_min=0;
    tempo.tm_sec=0;
    tempo.tm_mday=29;
    tempo.tm_mon=4;
    tempo.tm_year=2021-1900;
    tempo.tm_isdst=0;
    tempo.tm_wday=6;

    double som;

    som=60;
    tempo.tm_sec+=som;
    mktime(&tempo);
    printf("%d\n",tempo.tm_isdst);
    tempo.tm_sec+=som*som;
    mktime(&tempo);
    printf("%d\n",tempo.tm_isdst);
    memcpy(&tempo2,&tempo,sizeof(data));
    printf("sao: %s\n",asctime(&tempo));
    printf("%ld segundos\n",mktime(&tempo));
    
    tempo.tm_sec+=som;
    mktime(&tempo);
    printf("%ld segundos\n",mktime(&tempo));

    printf("Imprimir diff time %f\n",difftime(mktime(&tempo),mktime(&tempo2)));

}