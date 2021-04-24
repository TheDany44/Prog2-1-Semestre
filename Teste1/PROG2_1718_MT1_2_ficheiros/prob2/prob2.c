#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "vetor.h"

#define BUFFER 256

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 2 ***/
vetor* contar_remetente_destinatario(vetor *vrem, vetor *vdest)
{
	if(vrem==NULL || vdest==NULL){return NULL;}
	int i,k,flag=1;
	vetor *nomesdistintos;
	nomesdistintos=vetor_novo();
	if(nomesdistintos==NULL){return NULL;}

	for(i=0;i<vrem->tamanho;i++){ //insere em nomesdistintos todos os nomes que não existam lá de vrem
		flag=1;
		for(k=0;k<nomesdistintos->tamanho;k++){
			if(strcmp(vrem->elementos[i].str,nomesdistintos->elementos[k].str)==0){
				flag=0;
				break;
			}
		}
		if(flag){
			vetor_insere(nomesdistintos,vrem->elementos[i].str,-1);
		}

	}
	for(i=0;i<vdest->tamanho;i++){	//insere em nomesdistintos todos os nomes que não existam lá de vdest
		flag=1;
		for(k=0;k<nomesdistintos->tamanho;k++){
			if(strcmp(vdest->elementos[i].str,nomesdistintos->elementos[k].str)==0){
				flag=0;
				break;
			}
		}
		if(flag){
			if(vetor_insere(nomesdistintos,vdest->elementos[i].str,-1)==-1){return NULL;}
		}
	}
	int count;

	for(i=0;i<nomesdistintos->tamanho;i++){	//conta quantas vezes aparece, cada nome de nomesdistintos em vrem e vdest 
		count=0;
		for(k=0;k<vrem->tamanho;k++){
			if(strcmp(nomesdistintos->elementos[i].str,vrem->elementos[k].str)==0){
				count++;
			}
		}
		for(k=0;k<vdest->tamanho;k++){
			if(strcmp(nomesdistintos->elementos[i].str,vdest->elementos[k].str)==0){
				count++;
			}
		}
		printf("%s : %d cartas\n",nomesdistintos->elementos[i].str,count);
	}


	return nomesdistintos;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

void lerParaVetores(FILE* ficheiro, vetor* vrem, vetor *vdest, vetor *vcp_dest);

#define BUFFER 256

int main()
{
	FILE *fin;
	char linha[BUFFER];
	vetor* vrem;
	vetor* vdest;
	vetor *vcp_dest;
	vrem=NULL; vdest=NULL; vcp_dest=NULL;

	fin = fopen("correspondencia.txt", "r");
	if(fin == NULL)
	{
		printf("Erro ao abrir ficheiro.\n");
		return 1;
	}

	vrem = vetor_novo();
	vdest = vetor_novo();
	vcp_dest = vetor_novo();
	lerParaVetores(fin, vrem, vdest, vcp_dest);

	fclose(fin);

	vetor *cp = contar_remetente_destinatario(vrem, vdest);

	if (cp == NULL)
		printf("\nFuncao retornou erro.\n");
	else {
		printf("\nNumero de pessoas distintas: %d\n", vetor_tamanho(cp));
	}

	vetor_apaga(cp);

	return 0;
}


/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/
void lerParaVetores(FILE* ficheiro, vetor* vrem, vetor *vdest, vetor *vcp_dest)
{
	char buffer[256], *nlptr;

	if (ficheiro == NULL)
		return;

	while(fgets(buffer, 255, ficheiro) != NULL)
	{
		nlptr = strchr(buffer, '\n');
		if (nlptr)
			*nlptr = '\0';
		vetor_insere(vrem, buffer, -1);

		fgets(buffer, 255, ficheiro);
		nlptr = strchr(buffer, '\n');
		if (nlptr)
			*nlptr = '\0';
		vetor_insere(vdest, buffer, -1);

		fgets(buffer, 255, ficheiro);
		nlptr = strchr(buffer, '\n');
		if (nlptr)
			*nlptr = '\0';
		vetor_insere(vcp_dest, buffer, -1);
	}
}
