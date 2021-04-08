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

int maior_planalto (float * temperatura, int n){
    int count=1, i,max=0;
    float temp=-300;

    for(i=0;i<n;i++){
        if(temp==temperatura[i]){
            count++;
            if(max<count){
                max=count;
            }
        }
        else{
            count=1;
            temp=temperatura[i];
        }
    }
    return max;

}


int main(){
    float *temperatura;
    int tamanho=0;
    temperatura=NULL;
    
    temperatura=preenche_vetor(temperatura,&tamanho);

    printf("O maior planalto é: %d\n",maior_planalto(temperatura,tamanho));

    if(temperatura!=NULL){
        free(temperatura);
    }
    

    return 0;
}