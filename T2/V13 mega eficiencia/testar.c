#include <stdio.h>

int main(){
    int a,i;

    scanf("%d",&a);

    for(i=0;i<a*a;i++)
    {
        printf("%d\n",((a/2)+i*i+i)%a);
    }
    


}