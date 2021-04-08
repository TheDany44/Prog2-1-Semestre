#include <stdlib.h>
#include <stdio.h>

int zer(int *vetor,int tamanho){ 
    if(vetor==NULL || tamanho==0){return 0;}
    int i,minn=1000,temp,min;
    for(i=0;i<tamanho;i++){
        if(vetor[i]<0){
            temp=vetor[i]*(-1);
        }
        else{
            temp=vetor[i];
        }
        if(minn>temp){
            min=vetor[i];
            minn=temp;
        }
        else if(minn==temp){
            if(vetor[i]>min){
                min=vetor[i];
            }
        }
    }
    return min;
}


int main(){
    int tamanho,i,*vetor,n;

    scanf("%d",&tamanho);
    vetor=malloc(tamanho*sizeof(int));
    for(i=0;i<tamanho;i++){
        scanf("%d",vetor+i);
    }
    
    n=zer(vetor,tamanho);

    printf("%d\n",n);

    free(vetor);

    return 0;
}