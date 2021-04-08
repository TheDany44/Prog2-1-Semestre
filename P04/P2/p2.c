#include <stdio.h>
#include <stdlib.h>

float *preenche_vetor(float *temperatura, int *tamanho){
    float temp;
    printf("Insira um valor de temperatura ºC (insira -300 para terminar): \n");
    while(1){
        scanf("%f",&temp);
        if(temp==-300){return temperatura;}
        if(*tamanho==0){
            temperatura=malloc(sizeof(float));
        }
        else{
            temperatura=realloc(temperatura,(*tamanho+1)*(sizeof(float)));
        }
        if(temperatura==NULL){exit(1);}
        (*tamanho)++;
        temperatura[(*tamanho)-1]=temp;
        
    }
}

float * realce_temperaturas (float *temperatura, int n){
    float *realce,med;
    int i;
    realce=malloc(n*sizeof(float));
    if(realce==NULL||temperatura==NULL){return NULL;}

    for(i=0;i<n;i++){
        if(i==0){
            med=(temperatura[i]+temperatura[i+1])/2;
        }   
        else if(i==n-1){
            med=(temperatura[i]+temperatura[i-1])/2;
            printf("%.3f",med);
        }
        else{
            med=(temperatura[i-1]+temperatura[i]+temperatura[i+1])/3;
        }
        realce[i]=temperatura[i]-med;
    }
    return realce;
}


int main(){
    float *temperatura,*realce;
    int tamanho=0;
    temperatura=NULL;
    
    temperatura=preenche_vetor(temperatura,&tamanho);

    realce=realce_temperaturas(temperatura,tamanho);

    printf("[ ");
    for(int i=0;i<tamanho;i++){
        printf("%.3f ",realce[i]);
    }
    printf("]\n");

    if(temperatura!=NULL){
        free(temperatura);
        free(realce);
    }
    

    return 0;
}