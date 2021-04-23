#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pilha.h"

float calcula_total(char* expressao_rpn){
    char *token;
    pilha *pnum;
    pnum=pilha_nova();

    token=strstr(expressao_rpn,"\n");
    strcpy(token,"\0");

    token=strtok(expressao_rpn," ");

    int num;
    float num1,num2,r=1000000;
    while(token != NULL){
        
        if(strcmp(token,"0")==0){
            pilha_push(pnum,0);
        }
        else{
            num=atoi(token);
            if(num!=0){
                pilha_push(pnum,num);
            }
            else{
                if(r!=1000000){
                    num1=r;
                }else{
                    num1=(float)pnum->raiz->elemento;
                    pilha_pop(pnum);
                }
                
                num2=(float)pnum->raiz->elemento;
                pilha_pop(pnum);

                if(strcmp(token,"+")==0){
                    r=num1+num2;
                }
                if(strcmp(token,"-")==0){
                    r=num1-num2;
                }
                if(strcmp(token,"*")==0){
                    r=num1*num2;
                }
                if(strcmp(token,"/")==0){
                    r=num1/num2;
                }
            }
        }
        token=strtok(NULL," ");
    }
    
    return r;
}


int main(){
    printf("Expressão: ");

    char lido[100];
    fgets(lido,100,stdin);
    

    printf("Resultado: %.2f\n",calcula_total(lido));
    
    return 0;
}