#include <stdio.h>
#include <stdlib.h>

void preenche(float* v){
    int i;
    for(i=0;i<10;i++){
        printf("Introduza o %dº elemento: ",i+1);
        scanf(" %f",v+i);
    }
}

void print_v(float* v){
    int i;
    printf("Vetor: ");
    for(i=0;i<10;i++){
        printf("%.1f ",*(v+i));
    }
    printf("\n");

}

float avg(float* v){
    int i;
    float sum=0;
    for(i=0;i<10;i++){
        sum+=*(v+i);
    }
    return sum/10;
}

float max(float* v){
    int i;
    float max=*(v);
    for(i=1;i<10;i++){
        if (*(v+i)>max){
            max=*(v+i);
        }
    }
    return max;
}

float min(float* v){
    int i;
    float min=*(v);
    for(i=1;i<10;i++){
        if(*(v+i)<min){
            min=*(v+i);
        }
    }
    return min;
}

int main(){
    float *v;
    v=malloc(10*sizeof(float));
    preenche(v);
    printf("Média: %.2f\n",avg(v));
    printf("Máximo: %.1f\n",max(v));
    printf("Mínimo: %.1f\n",min(v));
    print_v(v);
    free(v);
    v=NULL;
    return 0;
}