
#include <stdio.h>

int main(){
    int i;

    for(i=0;i<26;i++){
        printf("%d %c\n",i+1,(char)(65+i));

    }

    return 0;
}