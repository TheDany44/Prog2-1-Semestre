#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "heap.h"

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 1.1 ***/

void contador(no_avl* aux, int *count, char inicio){

	if(aux==NULL){return;}

	
	if(aux->str[0]==inicio){
		(*count)++;
	}

	if(aux->esquerda!=NULL){
		contador(aux->esquerda,count,inicio);
	}
	if(aux->direita!=NULL){
		contador(aux->direita,count,inicio);
	}
	return;
}


int procura_inicio(no_avl *no, char inicio)
{
	/* complexidade do algoritmo: __O(logN)_____ */

	if(no==NULL){return 0;}

	int count=0;
	
	contador(no,&count,inicio);

	
	return count;
}

/*** problema 1.2 ***/
char* seleciona_por_ordem(heap *h, int k)
{
	if(h==NULL){return NULL;}
	
	int i;
	char* r,*apaga;
	heap* aux;
	aux=heap_nova(k);
	if(aux==NULL){return NULL;}
	r=NULL;

	for(i=1;i<=k;i++){
		free(r);
		if(!heap_insere(aux,h->elementos[1]->valor,h->elementos[1]->prioridade)){return NULL;}
		r=heap_remove(h);
		if(r==NULL){return NULL;}
	}

	for(i=1;i<=k;i++){
		if(!heap_insere(h,aux->elementos[1]->valor,aux->elementos[1]->prioridade)){return NULL;}
		apaga=heap_remove(aux);
		if(apaga==NULL){return NULL;}
		free(apaga);
	}
	heap_apaga(aux);

	return r;
}


/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

#define MAX_STR 500
#define MAX_LINE	100
#define MAX_SIZE 1000

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	FILE *fp=fopen("paises.txt", "r");
	char str_aux[MAX_STR], *res;
	
	/* inicio teste prob1.1 */
	{
		arvore_avl *arv;
		puts("\n* Problema 1.1 *");
		arv = avl_nova();
		while(fgets(str_aux,MAX_STR,fp) != NULL)
		{
			if(str_aux[strlen(str_aux)-1] == '\n')
				str_aux[strlen(str_aux)-1] = '\0';
			avl_insere(arv, str_aux);
		}
		
		printf("Numero de strings comecadas por 'a': %d\n", procura_inicio(arv->raiz, 'a'));
		printf("Numero de strings comecadas por 'b': %d\n", procura_inicio(arv->raiz, 'b'));
		printf("Numero de strings comecadas por 't': %d\n", procura_inicio(arv->raiz, 't'));
		printf("Numero de strings comecadas por 'z': %d\n", procura_inicio(arv->raiz, 'z'));

		avl_apaga(arv);
	}
	/* fim teste prob1.1 */

	rewind(fp);

	/* inicio teste prob1.2 */
	{
		heap* h=heap_nova(MAX_SIZE);
		char cidade[MAX_LINE]; 
		int prio=0, n=0;

		puts("\n* Problema 1.2 *");
	
		while(fgets(cidade, MAX_LINE, fp) != NULL)
		{
			*strchr(cidade, '\n') = '\0';
			heap_insere(h,cidade, (prio++)%20);
			n++;
		}
		
		res = seleciona_por_ordem(h,1);
		printf("Prioridade 1: %s\n", res != NULL ? res : "(null)");
		free(res);
		res = seleciona_por_ordem(h,25);
		printf("Prioridade 25: %s\n", res != NULL ? res : "(null)");
		free(res);
		res = seleciona_por_ordem(h,50);
		printf("Prioridade 50: %s\n", res != NULL ? res : "(null)");
		free(res);

		if(h->tamanho != n)
			printf("ERRO: heap foi alterada.\n");

		heap_apaga(h);
		puts("");
	}
	/* fim teste prob1.2 */

	fclose(fp);

	return 0;
}
