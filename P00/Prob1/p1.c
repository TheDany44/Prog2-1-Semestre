#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float function(float x,int a){
    return a*pow(x,2);
}

int main(){
    int a, min, max;
    float in, i;
    printf("Qual o valor de a? ");
    scanf(" %d",&a);
    printf("Qual o intervalo? ");
    scanf(" %d %d", &min,&max);
    printf("Qual o incremento? ");
    scanf(" %f",&in);
    for(i=min;i<=max;i+=in){
        printf("f(%.1f)=%.1f\n",i,function(i,a));
    }


    return 0;
}