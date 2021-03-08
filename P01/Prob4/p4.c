
#include <stdio.h>
#include <stdlib.h>


int main(){
    FILE *f;
    int extrair, largura, altura, bytespixel, pixel1[3],endereco, tamanhoarray=0,x,y,i;
    char RGB[3],aux;

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

    while (1==1){ 
        printf("Insira as coordenadas do pixel a ler (x,y): ");
        scanf(" %d %d",&x,&y);
        if (x>=800 || y>=533 || x<0 || y<0) {printf("Coordenadas inválidas.\n"); continue;}
        fseek(f,endereco+bytespixel*largura*(altura-1-y)+(bytespixel*x),SEEK_SET);
        fread(RGB,1,bytespixel,f);
        aux=RGB[2];
        RGB[2]=RGB[0];
        RGB[0]=aux;
        for(i=0;i<3;i++){ 
            printf("%d ", (int)RGB[i]);
        }
        printf("\n");
    }

    
    


    fclose(f);
    return 0;
}