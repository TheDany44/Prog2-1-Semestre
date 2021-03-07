 #include <stdio.h>   



int main(){
    char c;
    scanf(" %c",&c);
    printf("%d",(int)c);
    if ((c>=65) && (c<=90)){
        c = c + 32;
        printf("%c\n",c);
    }

    return 0;
}