#include <stdlib.h>
#include <stdio.h>

int ler_notas (float * notas){
    float notat, notap;
    int i=0;
    while(scanf("%f %f",&notat,&notap)!=0){
        if(notat==-1){break;}
        notas[i]=notat*0.6+notap*0.4;
        i++;
    }
    return i;
}

float media (float * notas, int n){
    float sum=0;
    int i;
    for(i=0;i<n;i++){
        if(notas[i]>=9.3 && notas[i]<9.5){
            notas[i]=9.5;
        }
        sum+=notas[i];
    }
    return sum/n;
}


int main(){
    float *notas;
    int numalunos;
    notas=calloc(100,sizeof(float));
    
    numalunos=ler_notas(notas);
    notas=realloc(notas,numalunos*sizeof(float));

    printf("A média das turmas foi: %.2f\n",media(notas,numalunos));

    free(notas);
    notas=NULL;
    return 0;
}