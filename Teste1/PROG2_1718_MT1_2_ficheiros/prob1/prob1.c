#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"
#include "pilha.h"


/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 1.1 ***/
lista* filtra_titulos(lista *lista1, lista *lista2)
{
	/* complexidade do algoritmo: _____O(N^2)_____ */
	if(lista1==NULL || lista2==NULL){return NULL;}
	lista *lsnova;
	lsnova=lista_nova();
	if(lsnova==NULL){return NULL;}


	int control;
	l_elemento *elemento,*elemento2;
	for(elemento=lista1->inicio;elemento!=NULL;elemento=elemento->proximo){
		control=1;
		for(elemento2=lista2->inicio;elemento2!=NULL;elemento2=elemento2->proximo){
			if(strcmp(elemento->str,elemento2->str)==0){
				control=0;
				break;
			}
		}
		if(control){
			if(lista_insere(lsnova,elemento->str,NULL)==NULL){return NULL;}
		}
	}	



	return lsnova;

}

/*** problema 1.2 ***/
int retira_comecados_por(lista *lst, char *inicio)
{
	if(lst==NULL){return 0;}

	l_elemento *elemento,*aux;
	int count=0;
	for(elemento=lst->inicio;elemento!=NULL;elemento=aux){
		aux=elemento->proximo;
		if(strncmp(elemento->str,inicio,strlen(inicio))==0){
			lista_remove(lst,elemento);
			count++;
		}
	}

	return count;
}

/*** problema 1.3 ***/
int insere_na_pilha(pilha *p, char *titulo)
{
	if(p==NULL){return 0;}

	pilhaItem *item;
	for(item=p->raiz;item!=NULL;item=item->proximo){	 //verifica se ja existe na pilha
		if(strcmp(item->elemento,titulo)==0){
			return 0;
		}
	}

	for(item=p->raiz;item!=NULL;item=item->proximo){
		if(strcmp(item->elemento,titulo)<0){
			break;
		}
	}

	pilha *aux;
	aux=pilha_nova();
	if(aux==NULL){return 0;}

	while(p->raiz!=item){
		pilha_push(aux,p->raiz->elemento);
		pilha_pop(p);
	}
	pilha_push(p,titulo);
	while (aux->raiz!=NULL)
	{
		pilha_push(p,aux->raiz->elemento);
		pilha_pop(aux);
	}
	pilha_apaga(aux);
	


	return 1;

}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

lista* lerParaLista(FILE* ficheiro)
{
	char buffer[256], *nlptr;
	lista* l;

	if (ficheiro == NULL)
		return NULL;

	l = lista_nova();

	while(fgets(buffer, 255, ficheiro) != NULL)
	{
		nlptr = strchr(buffer, '\n');
		if (nlptr)
		*nlptr = '\0';
		lista_insere(l,buffer,NULL);
	}

	return l;
}

pilha* lerParaPilha(FILE* ficheiro)
{
	char buffer[256], *nlptr;
	pilha* p;

	if (ficheiro == NULL)
		return NULL;

	p = pilha_nova();

	while(fgets(buffer, 255, ficheiro) != NULL)
	{
		nlptr = strchr(buffer, '\n');
		if (nlptr)
		*nlptr = '\0';
		pilha_push(p,buffer);
	}
	return p;
}

void imprimeLista(lista *l, unsigned int n) {
	if (l->tamanho<n)
		printf("ERRO... Lista possui menos de %d elementos\n",n);
	unsigned int i;
	l_elemento *aux = l->inicio;
	for (i=0; i<n; i++) {
		printf("%dº Livro: %s\n", i+1,aux->str);
		aux = aux->proximo;
	}
}

int main()
{
	FILE *f;
	lista *l1=NULL, *l2=NULL, *l=NULL;
	pilha *p;
	int nmov, res;
	char *tit1;

	/* testes */
	f = fopen("livros1.txt","r");
	if(f == NULL)
	{
		printf("Erro ao ler ficheiro de entrada.\n");
		return 1;
	}
	l1 = lerParaLista(f);
	fclose(f);

	f = fopen("livros2.txt","r");
	if(f == NULL)
	{
		printf("Erro ao ler ficheiro de entrada.\n");
		return 1;
	}
	l2 = lerParaLista(f);
	fclose(f);

	/* inicio teste prob1.1 */
	l = filtra_titulos(l1, l2);
	if(l) {
		printf("\nLista resultante contem %d livros.\n", lista_tamanho(l));
		if(lista_tamanho(l) != 12)
			printf("ERRO.. Tamanho da lista incorreto(tamanho: %d; esperado: 12)\n", lista_tamanho(l));
		else
			imprimeLista(l,lista_tamanho(l));
	}
	else
		printf("\nERRO.. filtra_titulos retornou NULL\n");
	/* fim teste prob1.1 */


	/* inicio teste prob1.2 */
	f = fopen("livros.txt","r");
	if(f == NULL)
	{
		printf("Erro ao ler ficheiro de entrada.\n");
		return 1;
	}
	lista_apaga(l);
	l = lerParaLista(f);
	fclose(f);

	nmov = retira_comecados_por(l, "A");
	printf("\nForam retirados %d livros\n", nmov);
	printf("A lista contém %d livros\n", lista_tamanho(l));
	if (nmov!=146)
		printf("ERRO.. Numero de livros removidos incorreto (removidos: %d; esperado: 146\n",nmov);
	else if(lista_tamanho(l) != 389)
		printf("ERRO.. Lista incorreta (tamanho: %d; esperado: 389)\n", lista_tamanho(l));
	else
		printf("9º livro da lista: %s\n", lista_elemento(l,8)->str);
	/* fim teste prob1.2 */


	/* inicio teste prob1.3 */
	f = fopen("livros2.txt","r");
	if(f == NULL)
	{
		printf("Erro ao ler ficheiro de entrada.\n");
		return 1;
	}
	p = lerParaPilha(f);
	fclose(f);

	tit1="Fora de Horas";
	res = insere_na_pilha(p, tit1);

	if (res==0) {
		printf("\n'%s' já existe na pilha\n", tit1);
		printf("Numero de elementos na pilha: %d\n", pilha_tamanho(p));
	}
	else if (pilha_tamanho(p) != 32)
		printf("\nERRO.. Numero de elementos na pilha incorreto (existentes: %d; esperado: 32)\n",pilha_tamanho(p));
	else {
		printf("\n'%s' foi inserido na pilha\n", tit1);
		printf("Numero de elementos na pilha: %d\n", pilha_tamanho(p));
	}

	tit1="Mundo incompleto";
	res = insere_na_pilha(p, tit1);

	if (res==0) {
		printf("'%s' já existe na pilha\n", tit1);
		printf("Numero de elementos na pilha: %d\n", pilha_tamanho(p));
	}
	else if (pilha_tamanho(p) != 32)
		printf("ERRO.. Numero de elementos na pilha incorreto (existentes: %d; esperado: 32)\n",pilha_tamanho(p));
	else {
			printf("'%s' foi inserido na pilha\n", tit1);
			printf("Numero de elementos na pilha: %d\n", pilha_tamanho(p));
		}
	puts("");
	pilhaItem *item;
	for(item=p->raiz;item!=NULL;item=item->proximo){
		printf("%s\n",item->elemento);
	}

	/* fim teste prob1.3 */

	lista_apaga(l);
	lista_apaga(l1);
	lista_apaga(l2);
	pilha_apaga(p);

	return 0;
}
