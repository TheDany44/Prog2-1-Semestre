#include <stdio.h>
#include <stdlib.h>

int main(){
    int size,i=1,k;
    size=31;
    printf("2\n");
    while(1){
        k=(2*i*i)%size;
        printf("%d\n",k);
        i++;
        if(i==size*size){
            break;
        }
        
    }
}