#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"
#include "fila.h"

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 1.1 ***/
lista* junta_nomes(lista *lst1, lista *lst2)
{
	/* complexidade do algoritmo: _____O(N)_________ */

	if(lst1==NULL || lst2==NULL){return NULL;}

	lista *lsnova;
	lsnova=lista_nova();
	if(lsnova==NULL){return NULL;}

	l_elemento *copiar;
	//copiar lista1
	for(copiar=lst1->inicio;copiar!=NULL;copiar=copiar->proximo){
		if(lista_insere(lsnova,copiar->str,NULL)==NULL){return NULL;}
	}
	for(copiar=lst2->inicio;copiar!=NULL;copiar=copiar->proximo){
		if(lista_insere(lsnova,copiar->str,NULL)==NULL){return NULL;}
	}


	return lsnova;
}

/*** problema 1.2 ***/
lista* lista_remove_duplicados(lista *lst)
{
	if(lst==NULL){return NULL;}

	l_elemento *procura,*remover,*aux;
	lista *lsnova;
	lsnova=lista_nova();
	if(lsnova==NULL){return NULL;}

	for(procura=lst->inicio;procura!=NULL;procura=procura->proximo){
		for(remover=procura->proximo;remover!=NULL;remover=aux){
			aux=remover->proximo;
			if(strcmp(procura->str,remover->str)==0){
				if(lista_insere(lsnova,remover->str,NULL)==NULL){return NULL;}

				lista_remove(lst,remover);
			}
		}
	}

	if(lsnova->tamanho==0){
		lista_apaga(lsnova);
		return NULL;
	}
	else{
		return lsnova;
	}
}

/*** problema 1.3 ***/
fila* pesquisa_nomes(lista *lst, char *nome)
{
	if(lst==NULL){return NULL;}

	fila *queue;
	queue=fila_nova();
	if(queue==NULL){return NULL;}

	l_elemento *elemento;
	for(elemento=lst->inicio;elemento!=NULL;elemento=elemento->proximo){
		if(strstr(elemento->str,nome)!=NULL){
			if(fila_push(queue,elemento->str)==-1){return NULL;}
		}
	}

	if(fila_tamanho(queue)==0){fila_apaga(queue); return NULL;}

	return queue;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

void lerParaLista(FILE* ficheiro, lista* l)
{
	char buffer[256], *nlptr;

	if (ficheiro == NULL || l == NULL)
		return;

	while(fgets(buffer, 255, ficheiro) != NULL)
	{
		nlptr = strchr(buffer, '\n');
		if (nlptr)
		*nlptr = '\0';
		lista_insere(l,buffer,NULL);
	}
}

int main()
{
	FILE *f;
	lista *l1=NULL, *l2=NULL, *l12=NULL, *l=NULL, *duplicados=NULL;
	fila *resultado=NULL;
	l_elemento *e;

	/* testes */
	f = fopen("nomes1.txt","r");
	if(f == NULL)
	{
		printf("Erro ao ler ficheiro de entrada.\n");
		return 1;
	}
	l12 = lista_nova();
	l1 = lista_nova();
	lerParaLista(f, l1);
	rewind(f);
	lerParaLista(f, l12);
	fclose(f);

	f = fopen("nomes2.txt","r");
	if(f == NULL)
	{
		printf("Erro ao ler ficheiro de entrada.\n");
		return 1;
	}
	l2 = lista_nova();
	lerParaLista(f, l2);
	rewind(f);
	lerParaLista(f, l12);
	fclose(f);

	/* inicio teste prob1.1 */
	l = junta_nomes(l1, l2);
	if(l)
		printf("\nLista resultante contem %d nomes.\n", lista_tamanho(l));
	else
		printf("\njunta_nomes retornou NULL\n");
	/* fim teste prob1.1 */

	/* inicio teste prob1.2 */
	duplicados = lista_remove_duplicados(l12);
	if(duplicados)
	{
		int n=0;
		printf("\nNomes duplicados (total de %d):\n", lista_tamanho(duplicados));
		for (e = duplicados->inicio; e != NULL && n<3; e = e->proximo, n++)
			printf("%s\n", e->str);
		if(lista_tamanho(duplicados)>5)
		{
			puts("...");
			for ( ; e->proximo != NULL; e = e->proximo);
			printf("%s\n", e->str);
		}
		else
			for ( ; e != NULL; e = e->proximo)
				printf("%s\n", e->str);
		if(lista_tamanho(l12) != 302)
			printf("Nem todos os nomes duplicados foram removidos da lista (tamanho: %d; esperado: 302)\n", lista_tamanho(l12));
	}
	else
		printf("\nlista_remove_duplicados retornou NULL\n");
	/* fim teste prob1.2 */

	/* inicio teste prob1.3 */
	resultado = pesquisa_nomes(l1, "SILVA");
	if(resultado)
	{
		int n=0;
		printf("\nNomes encontrados (%d): \n", fila_tamanho(resultado));
		while (!fila_vazia(resultado) && n<3) {
			printf("%s\n", fila_front(resultado));
			fila_pop(resultado);
			n++;
		}
		if(fila_tamanho(resultado) > 2)
		{
			puts("...");
			while (fila_tamanho(resultado) > 1)
				fila_pop(resultado);
			printf("%s\n", fila_front(resultado));
			fila_pop(resultado);
		}
		else {
			while (!fila_vazia(resultado)) {
					printf("%s\n", fila_front(resultado));
					fila_pop(resultado);
				}
		}
	}
	else
		printf("\npesquisa_nomes retornou NULL\n\n");
	/* fim teste prob1.3 */

	lista_apaga(l);
	lista_apaga(l1);
	lista_apaga(l12);
	lista_apaga(l2);
	lista_apaga(duplicados);
	fila_apaga(resultado);

	return 0;
}
