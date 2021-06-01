#include <stdio.h>

int primo(int num){
    int i;
    for(i=2;i<=num/2;i++){
        if(num%i==0){
            return primo(num+1);
        }
    }
    return num;
}

int main(){
    int num;
    while(1){
        scanf(" %d",&num);
        printf("Primo: %d\n",primo(num));
    }
}