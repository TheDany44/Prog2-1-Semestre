#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "vetor.h"
#include "pilha.h"

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 2 ***/
int avalia_expressoes(FILE *ficheiro, vetor *expressoes)
{
	if(ficheiro==NULL || expressoes==NULL){return 0;}

	int i,k,flag;
	pilha *control;
	

	for(i=0;i<expressoes->tamanho;i++){
		control=pilha_nova();
		if(control==NULL){return 0;}
		flag=0;
		for(k=0;k<strlen(expressoes->elementos[i].str);k++){
			if(expressoes->elementos[i].str[k]=='('){
				pilha_push(control,"a");
			}
			if(expressoes->elementos[i].str[k]==')'){
				if(control->raiz==NULL){
					flag=1;
					break;
				}
				pilha_pop(control);
			}
		}
		if(control->raiz!=NULL){
			flag=1;
		}
		fprintf(ficheiro,"%s -> ",expressoes->elementos[i].str);
		if(flag){
			fprintf(ficheiro,"NOK\n");
		}
		else{
			fprintf(ficheiro,"OK\n");
		}
		pilha_apaga(control);
	}

	


	return 1;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

#define BUFFER 256

vetor* lerFicheiro(FILE *ficheiro)
{
	char buffer[BUFFER], *charptr;
	vetor *v;
	v = vetor_novo();
	while(fgets(buffer, BUFFER, ficheiro) != NULL)
	{
		charptr = strchr(buffer, '\n');
		if(charptr) *charptr = '\0';
		charptr = strchr(buffer, '\t');
		if(charptr) *charptr = '\0';
		if(strcmp(charptr+1, "infixa") == 0)
			vetor_insere(v, buffer, v->tamanho);
	}
	return v;
}

int main()
{
	FILE *fin, *fout;
	vetor *expressoes=NULL;

	fin = fopen("expressoes.txt", "r");
	if(fin == NULL)
	{
		printf("Erro ao abrir ficheiro.\n");
		return 1;
	}

	fout = fopen("avaliacao.txt", "w");
	if(fout == NULL)
	{
		printf("Erro ao abrir ficheiro.\n");
		return 1;
	}

	expressoes = lerFicheiro(fin);
	if(!expressoes)
	{
		printf("Erro ao ler ficheiro de expressoes.\n");
		return 1;
	}

	if(avalia_expressoes(fout, expressoes) == 1)
		printf("Funcao terminou corretamente - verificar ficheiro avaliacao.txt\n");
	else
		printf("Funcao retornou erro.\n");

	fclose(fin);
	fclose(fout);

	return 0;
}
