#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *f;
    int c[2], counter[3], i,a;
    
    for(i=0;i<3;i++){
        counter[i]=0;
    }
    f = fopen("lusiadas-utf8.txt","r");

    c[0]= getc(f);
    while (!feof(f)){
        if (c[1]!=0)
            c[0]=c[1];
        c[1]= getc(f);
        
        if (c[0]==195){
            if ((c[1]==83) || (c[1]==163))
                counter[0]+=1;
            else if ((c[1] == 149)||(c[1]==181))
                counter[1]+=1;
            else if ((c[1]==135)||(c[1]==167))
                counter[2]+=1;
        }
        a++;
        
    }

    fclose(f);
    printf("Letra A com til: %d\n",counter[0]);
    printf("Letra O com til: %d\n",counter[1]);
    printf("Letra C com cedilha: %d\n",counter[2]);


    return 0;
}