#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vetor.h"
#include "heap.h"

/*** problema 2.1 ***/
vetor* heap_ordena(vetor *v)
{

	return NULL;
}

/*** problema 2.2 ***/
/*
complexidade do algoritmo:

justificacao:

*/


/* Aqui comeca o codigo de teste. Nao modificar! */

#define MAX_LINE	100

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);

	/* teste problema 2.1 */
	{
		int i, j;
		char cidade[MAX_LINE];
		vetor *v, *res;
		FILE *fp;

		puts("* Problema 2.1 *");
		v = vetor_novo();
		fp=fopen("cidades.txt", "r");
		while(fgets(cidade, MAX_LINE, fp) != NULL)
		{
			*strchr(cidade, ',') = '\0';
			vetor_insere(v,cidade,v->tamanho);
		}
		res=heap_ordena(v);
		if(res != NULL)
		{
			for(i=0; i<3 && i<vetor_tamanho(res); i++)
				printf("%s\n", vetor_elemento(res,i));
			if(vetor_tamanho(res) > 3)
			{
				if(vetor_tamanho(res) > 6)
					puts("...");
				j = i;
				if(vetor_tamanho(res)-3 > j)
					j = vetor_tamanho(res)-3;
				for (i=j; i<vetor_tamanho(res); i++)
					printf("%s\n", vetor_elemento(res,i));
			}
		}
		vetor_apaga(v);
		vetor_apaga(res);
	}

	return 0;
}
