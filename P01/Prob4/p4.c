
#include <stdio.h>
#include <stdlib.h>


int main(){
    FILE *f;
    int extrair, largura, altura, bytespixel, pixel1[3],endereco,x,y,i;

    f=fopen("imagem.bmp","rb"); 

    //imprime o tamanho do ficheiro
    fseek(f,2,SEEK_SET);                       
    fread(&extrair,4,1,f);
    printf("Tamanho total do ficheiro BMP: %d\n",extrair);

    //imprime a largura da imagem em pixeis
    fseek(f,12,SEEK_CUR);
    fread(&largura,4,1,f);
    printf("Largura da imagem: %d\n",largura);

    //imprime a altura da imagem me pixeis
    fread(&altura,4,1,f);
    printf("Altura da imagem: %d\n",altura);

    //imprime os bits ocupados por cada pixel no array de pixeis
    fseek(f,2,SEEK_CUR);
    extrair=0;
    fread(&extrair,4,1,f);
    bytespixel=extrair/8; //guarda em bytespixel o valor que cada pixel ocupa em bytes
    printf("Bits por pixel: %d\n",extrair);



    fseek(f,10,SEEK_SET);  
    fread(&endereco,4,1,f);  //endereco no qual comeca o array

    printf("(Para terminar o programa insire coordenadas negativas.)\n");
    char *RGB = calloc(4,1); 
    if (RGB==NULL){printf("Sem memória!\n"); exit(1);}
    while (1==1){ 
        printf("Insira as coordenadas do pixel a ler (x,y): ");
        scanf(" %d %d",&x,&y);
        if (x>=800 || y>=533) {printf("Coordenadas inválidas.\n"); continue;}
        if (x<0 || y<0) {break;}
        fseek(f,endereco+bytespixel*largura*(altura-1-y)+(bytespixel*x),SEEK_SET); //escolhe o pixel indicado 
        fread(RGB,1,bytespixel,f); //guarda o valor BGR do pixel
        *(RGB+3)=*(RGB+2); //troca BGR para RGB
        *(RGB+2)=*RGB;
        *RGB=*(RGB+3);
        for(i=0;i<3;i++){ 
            printf("%d ", *(RGB+i)); //imprime o valor RGB do pixel pedido
        }
        printf("\n");
    }

    

    fclose(f);
    return 0;
}