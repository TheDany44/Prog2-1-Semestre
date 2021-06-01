/*****************************************************************/
/*          Grafo direcionado | PROG2 | MIEEC | 2020/21          */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "grafo.h"
#include "heap.h"

grafo *grafo_novo()
{
    grafo *g = (grafo *)malloc(sizeof(grafo));
    g->tamanho = 0;
    g->nos = NULL;

    return g;
}

no_grafo *encontra_no(grafo *g, char *cidade)
{
    if (!g || !cidade)
        return NULL;

    // pesquisa por cidade no vetor de nós
    for (int i = 0; i < g->tamanho; i++)
    {
        if (strcmp(g->nos[i]->cidade, cidade) == 0)
            return g->nos[i];
    }
    return NULL;
}

no_grafo *no_insere(grafo *g, char *cidade)
{
    if (!g || !cidade)
        return NULL;

    // verifica se o nó já existe
    no_grafo *no = encontra_no(g, cidade);
    if (no)
        return NULL;

    // cria o novo nó para o user
    no = (no_grafo *)malloc(sizeof(no_grafo));
    if (!no)
        return NULL;

    // aloca espaço para o campo cidade
    no->cidade = (char *)malloc((strlen(cidade) + 1) * sizeof(char));
    if (!no->cidade)
    {
        free(no);
        return NULL;
    }
    // inicializa todos os campos
    strcpy(no->cidade, cidade);
    no->tamanho = 0;
    no->arestas = NULL;
    no->p_acumulado = 0;
    no->anterior = NULL;
    no->dataatualizada = NULL;

    // insere o nó criado no final do vetor de nós
    g->nos = (no_grafo **)realloc(g->nos, (g->tamanho + 1) * sizeof(no_grafo *));
    if (!g->nos)
    {
        free(no->cidade);
        free(no);
        return NULL;
    }
    // incrementa o tamanho do numero de nós e insere no vetor de apontadores de nós
    g->tamanho++;
    g->nos[g->tamanho - 1] = no;

    return no;
}

// função auxiliar que retorna 1 se existir a aresta para destino ou 0,
// se a aresta não existir, -1 se der erro
int existe_aresta(no_grafo *origem, no_grafo *destino, char *codigo)
{

    if (!origem || !destino)
        return -1;

    //pesquisa em todas as arestas se existe
    for (int i = 0; i < origem->tamanho; i++)
    {

        if ((origem->arestas[i]->destino == destino) && ((strcmp(origem->arestas[i]->codigo, codigo) == 0)))
            return 1;
    }

    return 0;
}

int cria_aresta(no_grafo *origem, no_grafo *destino, char *codigo, char *companhia, data partida, data chegada, float preco, int lugares)
{
    if (!origem || !destino || !codigo || !companhia)
        return -1;

    if (preco < 0 || lugares < 0)
        return -1;

    // verifica se a ligação já existe
    if (existe_aresta(origem, destino, codigo) > 0)
        return -1;

    // cria a nova ligação
    aresta_grafo *ag = (aresta_grafo *)malloc(sizeof(aresta_grafo));
    if (!ag)
        return -1;

    ag->destino = destino;
    ag->preco = preco;
    ag->lugares = lugares;
    // aloca espaço para o código
    ag->codigo = (char *)malloc((strlen(codigo) + 1) * sizeof(char));
    if (!ag->codigo)
    {
        free(ag);
        return -1;
    }
    strcpy(ag->codigo, codigo);
    // aloca espaço para o companhia
    ag->companhia = (char *)malloc((strlen(companhia) + 1) * sizeof(char));
    if (!ag->companhia)
    {
        free(ag->codigo);
        free(ag);
        return -1;
    }
    strcpy(ag->companhia, companhia);

    // inicializa todos os campos
    ag->partida.tm_year = partida.tm_year;
    ag->partida.tm_mon = partida.tm_mon;
    ag->partida.tm_mday = partida.tm_mday;
    ag->partida.tm_hour = partida.tm_hour;
    ag->partida.tm_min = partida.tm_min;
    ag->partida.tm_sec = 0;
    ag->partida.tm_isdst = 0;

    // inicializa todos os campos
    ag->chegada.tm_year = chegada.tm_year;
    ag->chegada.tm_mon = chegada.tm_mon;
    ag->chegada.tm_mday = chegada.tm_mday;
    ag->chegada.tm_hour = chegada.tm_hour;
    ag->chegada.tm_min = chegada.tm_min;
    ag->chegada.tm_sec = 0;
    ag->chegada.tm_isdst = 0;

    // insere a nova ligação no vetor de ligações
    origem->arestas = (aresta_grafo **)realloc(origem->arestas, (origem->tamanho + 1) * sizeof(aresta_grafo *));
    if (!origem->arestas)
    {
        free(ag->codigo);
        free(ag->companhia);
        free(ag);
        return -1;
    }
    origem->tamanho++;
    origem->arestas[origem->tamanho - 1] = ag;

    return 0;
}

no_grafo *no_remove(grafo *g, char *cidade)
{
    //encontrar o no - FEITO
    //apagar arestas do no - FEITO ???????????????
    //reduzir tamanho do grafo - FEITO 
    //mover tudo para a esquerda - FEITO
    //realloc -1 - FEITO
    //pesquisar quais arestas apontam para o no e apagar - FEITO
    

    if(g==NULL || cidade==NULL){
        return NULL;
    }

    //Vê se ele existe
    no_grafo *encontra;
    encontra=encontra_no(g,cidade);     
    if(encontra==NULL){return NULL;}

    int i;
    //remove todas as arestas do nó
    for(i=0;i<encontra->tamanho;i++){       
        if(aresta_apaga(encontra->arestas[i])==-1){
            return NULL;
        }
    }
    encontra->tamanho=0;
    free(encontra->arestas);
    encontra->arestas=NULL;

    //apaga no
    int pos,k;
    for(i=0;i<g->tamanho;i++){  //descobre indice 
        if(g->nos[i]==encontra){
            pos=i;
            break;
        }
    }
    for(k=pos;k<g->tamanho-1;k++){  //puxa tudo para a esquerda
        g->nos[k]=g->nos[k+1];
    }
    g->tamanho--; //diminui tamanho grafo
    g->nos=realloc(g->nos,g->tamanho*sizeof(no_grafo**)); //diminui memoria
    if(g->nos==NULL){return NULL;}

    //pesquisar quais arestas apontam para o no e apagar
    for(i=0;i<g->tamanho;i++){   //viaja nos

        for(k=0;k<g->nos[i]->tamanho;k++){      //viaja arestas

            if(g->nos[i]->arestas[k]->destino==encontra){       //se alguma aresta apontar para o no a retirar, apaga aresta
                
                aresta_apaga(g->nos[i]->arestas[k]);

                for(pos=k;pos<g->nos[i]->tamanho-1;pos++){      //corrige vetor aresta
                    g->nos[i]->arestas[pos]=g->nos[i]->arestas[pos+1];
                }
                k--;
                g->nos[i]->tamanho--;
                
                g->nos[i]->arestas=realloc(g->nos[i]->arestas,g->nos[i]->tamanho*sizeof(aresta_grafo*));
                if(g->nos[i]->arestas==NULL && g->nos[i]->tamanho!=0){return NULL;}
            }
        }
    }
    
    return encontra;
}

int aresta_apaga(aresta_grafo *aresta)
{
    if(aresta==NULL){return -1;}

    free(aresta->codigo);
    free(aresta->companhia);
    free(aresta);

    return 0;
}

int no_apaga(no_grafo *no)
{
    if(no==NULL){return -1;}

    free(no->cidade);

    int i;
    for(i=0;i<no->tamanho;i++){
        if(aresta_apaga(no->arestas[i])==-1){
            return -1;
        }
    }
    free(no->arestas);
    free(no);

    return 0;
}

void grafo_apaga(grafo *g)
{
    if(g==NULL){
        return;
    }

    int i;
    for(i=0;i<g->tamanho;i++){
        if(no_apaga(g->nos[i])==-1){
            return;
        }
    }
    free(g->nos);
    free(g);
    return;
}

no_grafo *encontra_voo(grafo *g, char *codigo, int *aresta_pos)
{
    //procurar em todos os nos as arestas e retirar
    if(g==NULL || codigo==NULL || aresta_pos==NULL){return NULL;}

    int i,k;
    for(i=0;i<g->tamanho;i++){
        for(k=0;k<g->nos[i]->tamanho;k++){
            if(strcmp(g->nos[i]->arestas[k]->codigo,codigo)==0){
                *aresta_pos=k;
                return g->nos[i];
            }
        }
    }

    return NULL;
}

no_grafo **pesquisa_avancada(grafo *g, char *destino, data chegada, double preco_max, int *n)
{
    if(g==NULL || destino==NULL || preco_max<0 || n==NULL){return NULL;}

    no_grafo **vetor;
    vetor=NULL;
    (*n)=0;

    int i,k,j,flag=0;
    for(i=0;i<g->tamanho;i++){ //viaja por todos os nos
        for(k=0;k<g->nos[i]->tamanho;k++){  //viaja por todas as arestas de cada no
            if(strcmp(g->nos[i]->arestas[k]->destino->cidade,destino)==0){   //verifica se voo corresponde as condiçoes necessárias
                if(chegada.tm_mday==g->nos[i]->arestas[k]->chegada.tm_mday && chegada.tm_mon==g->nos[i]->arestas[k]->chegada.tm_mon && chegada.tm_year==g->nos[i]->arestas[k]->chegada.tm_year && g->nos[i]->arestas[k]->preco<=preco_max){
                    flag=0;
                    for(j=0;j<*n;j++){    //verifica se ainda nao existe
                        if(vetor[j]==g->nos[i]){
                            flag=1;
                            break;
                        }
                    }
                    if(!flag){      //se não existir coloca
                        vetor=realloc(vetor,(*n)*sizeof(no_grafo*));
                        (*n)++;
                        vetor[*n-1]=g->nos[i];
                    }
                }
            }
        }
    }


    return vetor;
}

no_grafo **trajeto_mais_rapido(grafo *g, char *origem, char *destino, data partida, int *n)
{
    return NULL;
}

no_grafo **menos_transbordos(grafo *g, char *origem, char *destino, data partida, int *n)
{
    return NULL;
}

aresta_grafo **atualiza_lugares(char *ficheiro, grafo *g, int *n)
{
    //abrir ficheiro
    //ler e mudar valores de lugares
    //se ficar 0 remover e acrescentar a vetor
    if(ficheiro==NULL || g==NULL || n==NULL){return NULL;}

    FILE *f;
    f=fopen(ficheiro,"r");
    if(f==NULL){return NULL;}
    char linha[101],*token,codigo[50];
    int lugares, arestaindice,i;
    no_grafo *noencontrado;
    aresta_grafo **vetor;
    vetor=NULL;
    (*n)=0;

    while(fgets(linha,100,f)!=NULL){
        token=strstr(linha,"\n");
        if(token!=NULL){*token='\0';}

        token=strtok(linha,",");
        if(token==NULL){continue;}
        strcpy(codigo,token);

        token=strtok(NULL,",");
        if(token==NULL){continue;}
        lugares=atoi(token);

        noencontrado=encontra_voo(g,codigo,&arestaindice);
        noencontrado->arestas[arestaindice]->lugares=lugares;

        if(lugares==0){
            (*n)++;
            vetor=realloc(vetor,(*n)*sizeof(aresta_grafo*));
            vetor[*n-1]=noencontrado->arestas[arestaindice];

            for(i=arestaindice;i<noencontrado->tamanho-1;i++){
                noencontrado->arestas[i]=noencontrado->arestas[i+1];
            }
            noencontrado->tamanho--;
            noencontrado->arestas=realloc(noencontrado->arestas,noencontrado->tamanho*sizeof(aresta_grafo*));
            if(noencontrado->arestas==NULL && noencontrado->tamanho!=0){return NULL;}
        }

    }
    fclose(f);
    return vetor;
}

grafo *grafo_importa(const char *nome_ficheiro)
{
    if (nome_ficheiro == NULL)
        return NULL;

    FILE *f = fopen(nome_ficheiro, "r");
    if (f == NULL)
        return NULL;

    grafo *g = grafo_novo();
    if (g == NULL)
    {
        fclose(f);
        return NULL;
    }
    char str[500] = {0}, codigo[15] = {0}, origem[50] = {0}, destino[50] = {0}, companhia[4] = {0};
    int lugares = 0;
    double preco = 0;
    struct tm partida, chegada;

    char *token;
    no_grafo *no_origem, *no_destino;
    int ret;
    while (fgets(str, 500 * sizeof(char), f) != NULL)
    {
        str[strlen(str) - 1] = '\0';

        token = strtok(str, ",");
        if (!token)
            break;
        strcpy(codigo, token);

        token = strtok(NULL, ",");
        strcpy(origem, token);

        token = strtok(NULL, ",");
        strcpy(destino, token);

        token = strtok(NULL, ",");
        partida.tm_year = atoi(token);

        token = strtok(NULL, ",");
        partida.tm_mon = atoi(token) - 1;

        token = strtok(NULL, ",");
        partida.tm_mday = atoi(token);

        token = strtok(NULL, ",");
        partida.tm_hour = atoi(token);

        token = strtok(NULL, ",");
        partida.tm_min = atoi(token);

        token = strtok(NULL, ",");
        chegada.tm_year = atoi(token);

        token = strtok(NULL, ",");
        chegada.tm_mon = atoi(token) - 1;

        token = strtok(NULL, ",");
        chegada.tm_mday = atoi(token);

        token = strtok(NULL, ",");
        chegada.tm_hour = atoi(token);

        token = strtok(NULL, ",");
        chegada.tm_min = atoi(token);

        token = strtok(NULL, ",");
        preco = atof(token);

        token = strtok(NULL, ",");
        lugares = atoi(token);

        token = strtok(NULL, ",");
        strcpy(companhia, token);

        // procura no grafo um nó com o nome da origem
        no_origem = encontra_no(g, origem);
        // se o nó ainda não existe, cria-o e insere-o no grafo
        if (!no_origem)
        {

            no_origem = no_insere(g, origem);

            if (!no_origem)
            {
                fclose(f);
                return NULL;
            }
        }
        // procura no grafo um nó com o nome do destino
        no_destino = encontra_no(g, destino);

        // se o nó ainda não existe, cria-o e insere-o no grafo
        if (!no_destino)
        {
            no_destino = no_insere(g, destino);

            if (!no_destino)
            {
                fclose(f);
                return NULL;
            }
        }

        if (existe_aresta(no_origem, no_destino, codigo) == 0)
        {

            ret = cria_aresta(no_origem, no_destino, codigo, companhia, partida, chegada, preco, lugares);

            if (ret == -1)
            {
                fclose(f);
                return NULL;
            }
        }
    }

    fclose(f);
    return g;
}
