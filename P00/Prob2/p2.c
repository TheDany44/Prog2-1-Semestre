#include <stdio.h>
#include <stdlib.h>

void vetor(int *v){
    int i;
    for(i=0;i<5;i++){
        printf("Introduza %dº numero: ",i+1);
        scanf(" %d",v+i);
    }
}

void common(int *v1, int *v2){
    int i,a,size=0,b, control=1;
    int *v3;
    v3=malloc(5*sizeof(int));
    for(i=0;i<5;i++){
        for(a=0;a<5;a++){
            if(*(v1+i)==*(v2+a)){
                for(b=0;b<=size;b++){
                    if(*(v1+i)==*(v3+b)){
                        control=0;
                        break;
                    }
                }
                if (control) {printf("%d ",*(v1+i));
                    *(v3+size)=*(v1+i);
                    size++;
                }
                control = 1;
            }
        }
    }
    printf("\n");
    free(v3);
    v3=NULL;
}


int main(){
    int *v1, *v2;
    v1 = malloc(5*sizeof(int));
    v2 = malloc(5*sizeof(int));

    printf("Vetor 1:\n");
    vetor(v1);
    printf("Vetor 2:\n");
    vetor(v2);
    printf("\nComuns: ");
    common(v1,v2);
    free(v1);
    v1=NULL;
    free(v2);
    v2=NULL;

    return 0;
}