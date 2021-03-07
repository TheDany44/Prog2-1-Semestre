#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
    FILE *f;
    char titulo[31], artista[31], album[31], ano[5],comentario[31];
    int faixa, byteZero, gen;
    
    f=fopen("musica.mp3","rb");
    
    fseek(f,-1,SEEK_END);
    fread(&gen,1,1,f);

    fseek(f,-3,SEEK_CUR);
    fread(&byteZero,1,1,f);

    if(byteZero == 0){
        fseek(f,0,SEEK_CUR);
        fread(&faixa,1,1,f);

        fseek(f,-30,SEEK_CUR);
        fread(comentario,1,28,f);
        comentario[strlen(comentario)]='\0';

        fseek(f,-28,SEEK_CUR);
    }
    else{
        fseek(f,-28,SEEK_CUR);
        fread(comentario,1,30,f);
        comentario[strlen(comentario)]='\0';

        fseek(f,-30,SEEK_CUR);
    }

    fseek(f,-4,SEEK_CUR);
    fread(ano,1,4,f);
    ano[4]='\0';

    fseek(f,-34,SEEK_CUR);
    fread(album,1,30,f);
    album[strlen(album)]='\0';

    fseek(f,-60,SEEK_CUR);
    fread(artista,1,30,f);
    artista[strlen(artista)]='\0';

    fseek(f,-60,SEEK_CUR);
    fread(titulo,1,30,f);
    titulo[strlen(titulo)]='\0';

    fclose(f);

    printf("Título - %s\n",titulo);
    printf("Artista - %s\n",artista);
    printf("Album - %s\n",album);
    printf("Ano - %s\n",ano);
    printf("Numero - %d\n",faixa);
    printf("Género - %d\n",gen);
    return 0;
}