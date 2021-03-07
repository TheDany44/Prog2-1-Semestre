
#include <stdio.h>
#include <stdlib.h>


int main(){
    FILE *f;
    int extrair, largura, altura, bytespixel, pixel1[3],endereco, tamanhoarray=0, RBG[3],x,y;


    f=fopen("imagem.bmp","rb");

    fseek(f,2,SEEK_SET);                       
    fread(&extrair,4,1,f);
    printf("Tamanho total do ficheiro BMP: %d\n",extrair);

    fseek(f,12,SEEK_CUR);
    fread(&largura,4,1,f);
    printf("Largura da imagem: %d\n",largura);

    fread(&altura,4,1,f);
    printf("Altura da imagem: %d\n",altura);

    fseek(f,2,SEEK_CUR);
    extrair=0;
    fread(&extrair,4,1,f);
    bytespixel=extrair/8;
    printf("Bits por pixel: %d %d\n",extrair,bytespixel);



    fseek(f,10,SEEK_SET);  
    fread(&endereco,4,1,f);  //endereco no qual comeca o array

    fseek(f,20,SEEK_CUR);
    fread(&tamanhoarray,4,1,f);

    printf("Escolha o X e o Y do pixel que quer ler: ");
    scanf(" %d %d",&x,&y);
    fseek(f,endereco+(3*y),SEEK_SET);



    extrair=0;
    fread(&extrair,1,1,f);
    printf("%d",extrair);



    
    


    fclose(f);
    return 0;
}