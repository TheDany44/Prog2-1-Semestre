#include "armazem.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * funcoes do armazem
 */
/* alinea b) */
armazem* armazem_novo(int comprimento, int altura)
{
	if(comprimento<1 || altura <1){return NULL;}
	armazem *apdl;

	apdl=malloc(sizeof(armazem));
	if(apdl==NULL){return NULL;}

	apdl->altura=altura;
	apdl->comprimento=comprimento;

	apdl->contentores=malloc(sizeof(fila));
	if(apdl->contentores==NULL){free(apdl);return NULL;}

	apdl->contentores->tamanho=0;
	apdl->contentores->raiz=NULL;

	return apdl;
}

/* alinea c) */
int armazem_vazio(armazem* armz)
{
	if(armz==NULL){return 1;}

	if(armz->contentores->tamanho==0){
		return 1;
	}

	return 0;
}

/* alinea d) */
int armazem_cheio(armazem* armz)
{
	/* devolve nao cheio */
	if(armz==NULL){return 0;}

	if(armazem_vazio(armz)){return 0;}

	if(armz->comprimento==armz->contentores->tamanho){
		pilha *ultimo;

		ultimo=fila_back(armz->contentores);
		
		if(ultimo->tamanho==armz->altura){return 1;}
	}

	return 0;
}

/* alinea e) */
int armazenar_contentor(armazem* armz, contentor* contr)
{
	/* devolve nao ha' espaco */
	if(armz==NULL || contr==NULL){return 0;}

	if(armazem_cheio(armz)==1){return 0;}

	if(armazem_vazio(armz)==1){

		pilha *nova_pilha;
		nova_pilha=pilha_nova();
		if(nova_pilha==NULL){return 0;}

		pilha_push(nova_pilha,contr);

		fila_push(armz->contentores,nova_pilha);
		
		return 1;

	}

	pilha *ultimo;
	ultimo=fila_back(armz->contentores);
	
	if(ultimo->tamanho<armz->altura){
		pilha_push(ultimo,contr);
	}
	else{
		pilha *new;

		new=pilha_nova();
		if(new==NULL){return 0;}

		pilha_push(new,contr);

		fila_push(armz->contentores,new);

	}
	return 1;
}

/* alinea f) */
contentor* expedir_contentor(armazem* armz)
{
	if(armz==NULL || armazem_vazio(armz)==1){return NULL;}

	contentor *saida;

	saida=contentor_novo(armz->contentores->raiz->elemento->raiz->elemento->destino,armz->contentores->raiz->elemento->raiz->elemento->valor);
	

	pilhaItem *aux;
	aux=armz->contentores->raiz->elemento->raiz;
	if(aux->proximo==NULL){
		fila_pop(armz->contentores);
	}
	else{ 
		armz->contentores->raiz->elemento->raiz=aux->proximo;
		armz->contentores->raiz->elemento->tamanho--;
		contentor_apaga(aux->elemento);
		free(aux);
	}

	
	return saida;
}
