#include <stdio.h>
#include <stdlib.h>
#include "plantas.h"
#include <time.h>
#include <string.h>

int main(){
    FILE *f;
    char files[200],*token;
    int i,linhacount,a,b,tam,*l;
    char linha[500],**linhabaralha,**linhabaralhada;
    srand(time(0));
    

    for(i=0;i<1000;i++){
        f=fopen("db_small.txt","r");    
        linhacount=0;
        tam=0;

        while(fgets(linha,500,f)!=NULL){
            
            if(linhacount==0){
                linhabaralha=malloc(sizeof(char*));
            }
            else{
                linhabaralha=realloc(linhabaralha,(linhacount+1)*sizeof(char*));
            }
            linhabaralha[linhacount]=malloc((strlen(linha)+1)*sizeof(char));

            strcpy(linhabaralha[linhacount],linha);
            linhacount++;

        }
        fclose(f);
        l=malloc(linhacount*sizeof(int));
        linhabaralhada=malloc(linhacount*sizeof(char*));
        linhacount++;
        printf("sss\n");
        for(a=0;a<linhacount-1;a++){
            tam++;
            l[a]=rand()%linhacount;

            for(b=0;b<tam-1;b++){
                if(l[a]==l[b]){
                    l[a]=rand()%linhacount;
                    b=0;
                }
            }

            linhabaralhada[l[a]]=linhabaralha[a];
        }


        sprintf(files,"Ficheiros/%d.txt",i);
        f=fopen(files,"w");

        for(a=0;a<linhacount;a++){
            fprintf(f,"%s",linhabaralhada[a]);
        }

        fclose(f);
        
        //limpa
        free(linhabaralhada);
        for(a=0; a<linhacount;a++){
            free(linhabaralha[i]);
        }
        free(linhabaralha);

        free(l);
    }

    return 0;
}