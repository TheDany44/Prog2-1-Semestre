#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabdispersao.h"

tabela_dispersao* base_de_dados(){
    FILE *f;
    f=fopen("passwords.txt","r");

    char linha[200],*token,user[100];

    tabela_dispersao *tab;

    tab=tabela_nova(10,hash_djbm);

    while(fgets(linha,200,f)!=NULL){
        token=strstr(linha,"\n");
        if(token!=NULL){*token='\0';}

        token=strtok(linha," ");
        if(token==NULL){continue;}
        strcpy(user,token);

        token=strtok(NULL," ");
        if(token==NULL){continue;}

        if(tabela_adiciona(tab,token,user)!=0){return NULL;}
    }



    fclose(f);
    return tab;
}

int main(){
    tabela_dispersao *tab;

    tab=base_de_dados();
    if(tab==NULL){return 0;}
    char user[100], pass[100];
    const char *aux;

    while(1){
        printf("Login: ");
        scanf(" %s",user);
        printf("Password: ");
        scanf(" %s",pass);


        aux=tabela_valor(tab,pass);
        if(aux==NULL){
            printf("Authentication Failed\n");
            continue;
        }
        
        if(strcmp(aux,user)!=0){
            printf("Authentication Failed\n");
        }
        else{
            printf("Authentication Succeeded\n");
        }
    }
    

    return 0;
}