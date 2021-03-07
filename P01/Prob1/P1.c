#include <stdio.h>
#include <stdlib.h>

void convert(int *letra){
    if ((*letra >= 65) && (*letra <= 90)){
        *letra += 32;
    }
    else if (((*letra  >= 192)&&(*letra <= 195)) || ((*letra >= 224)&&(*letra  <= 227)))
        *letra = 97;
    else if (((*letra  >= 211)&&(*letra  <= 213)) || ((*letra  >= 243)&&(*letra  <= 245)))
        *letra = 111;
    else if((*letra  == 201) || (*letra == 202) || (*letra == 233) || (*letra == 234))
        *letra = 101;
    else if((*letra == 205) || (*letra == 237))
        *letra = 105;
    else if ((*letra == 199)||(*letra == 231))
        *letra = 99;
    else if((*letra == 218) || (*letra == 250))
        *letra = 117;
    
}


int main(){
    FILE *f;
    int counter=0 , aux, i, c;
    float letter[26];
    for(i=0;i<26;i++){
        letter[i] = 0;
    }
    f = fopen("lusiadas.txt","r");

    while (!feof(f)){
        c = getc(f);
        convert(&c);
        if ((c>=97) && (c<=122)){
            counter+=1;
            aux = c - 97;
            letter[aux]+=1;
        }
    }
    fclose(f);

    printf("Número de letras no ficheiro: %d\n",counter);
    for(i=0;i<26;i++){
        letter[i]=(letter[i]/counter)*100;
        printf("Letra %c = %.2f%%\n",(int)'a'+i,letter[i]);
    }

    return 0;
}
