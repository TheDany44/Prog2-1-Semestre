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

int retira_vetor_nos(grafo* g,int pos){
    if(g==NULL || pos<0){return 0;}
    if(pos>=g->tamanho){return 0;}

    int i;
    g->tamanho--;
    for(i=pos;i<g->tamanho;i++){
        g->nos[i]=g->nos[i+1];
    }
    g->nos=realloc(g->nos,g->tamanho*sizeof(no_grafo*));
    if(g->nos==NULL && g->tamanho!=0){return 0;}
    return 1;
}

int retira_vetor_aresta(no_grafo* no,int pos){
    if(no==NULL || pos<0){return 0;}
    if(pos>=no->tamanho){return 0;}

    int i;
    no->tamanho--;
    for(i=pos;i<no->tamanho;i++){
        no->arestas[i]=no->arestas[i+1];
    }
    no->arestas=realloc(no->arestas,no->tamanho*sizeof(aresta_grafo*));
    if(no->arestas==NULL && no->tamanho!=0){return 0;}
    return 1;
}

int apaga_vetor_arestas(no_grafo* no){
    if(no==NULL){return 0;}

    int i;
    for(i=0;i<no->tamanho;i++){
        if(aresta_apaga(no->arestas[i])<0){return 0;}
    }
    if(no->tamanho!=0){
        free(no->arestas);
    }
    
    no->arestas=NULL;
    no->tamanho=0;

    return 1;
}

no_grafo *no_remove(grafo *g, char *cidade)
{
    //encontrar o no - FEITO
    //retirar o no e corrigir grafo - FEITO
    //apagar arestas do no - FEITO
    //pesquisar quais arestas apontam para o no e apagar - FEITO
    if(g==NULL || cidade==NULL){return NULL;}

    int n=-1,i;
    no_grafo *encontrado;

    //encontra no e indice
    for(i=0;i<g->tamanho;i++){
        if(strcmp(g->nos[i]->cidade,cidade)==0){
            n=i;
            encontrado=g->nos[i];
        }
    }
    if(n==-1){return NULL;}
    //retira no
    if(!retira_vetor_nos(g,n)){return NULL;}

    //apaga arestas do no
    if(!apaga_vetor_arestas(encontrado)){return NULL;}

    //pesquisa e apaga aresta igual
    int k;
    for(i=0;i<g->tamanho;i++){
        for(k=0;k<g->nos[i]->tamanho;k++){
            if(g->nos[i]->arestas[k]->destino==encontrado){
                if(aresta_apaga(g->nos[i]->arestas[k])<0){return NULL;}
                
                if(!retira_vetor_aresta(g->nos[i],k)){return NULL;}
                k--;
            }
        }
    }
    return encontrado;
}

int aresta_apaga(aresta_grafo *aresta)
{
    if(aresta==NULL){return -1;}

    free(aresta->codigo);
    free(aresta->companhia);
    free(aresta);
    aresta=NULL;

    return 0;
}

int no_apaga(no_grafo *no)
{
    if(no==NULL){return -1;}

    free(no->cidade);
    if(!apaga_vetor_arestas(no)){return -1;};
    free(no);
    no=NULL;

    return 0;
}

void grafo_apaga(grafo *g)
{
    if(g==NULL){return;}

    int i;
    for(i=0;i<g->tamanho;i++){
        if(no_apaga(g->nos[i])!=0){return;}
    }
    free(g->nos);
    free(g);
    g=NULL;
    return;
}

no_grafo *encontra_voo(grafo *g, char *codigo, int *aresta_pos)
{
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

int compara_vetor_nos(no_grafo** vetor,int tam, no_grafo* no){
    if(vetor==NULL && tam!=0){return 1;}
    int i;
    for(i=0;i<tam;i++){
        if(vetor[i]==no){return 1;}
    }
    return 0;
}

no_grafo **pesquisa_avancada(grafo *g, char *destino, data chegada, double preco_max, int *n)
{
    if(g==NULL || destino==NULL || preco_max<0 || n==NULL){return NULL;}

    int i,k;
    no_grafo** vetor;
    vetor=NULL;
    (*n)=0;
    for(i=0;i<g->tamanho;i++){
        for(k=0;k<g->nos[i]->tamanho;k++){
            if(strcmp(g->nos[i]->arestas[k]->destino->cidade,destino)==0 && g->nos[i]->arestas[k]->chegada.tm_mday==chegada.tm_mday && g->nos[i]->arestas[k]->chegada.tm_mon==chegada.tm_mon && g->nos[i]->arestas[k]->chegada.tm_year==chegada.tm_year && g->nos[i]->arestas[k]->preco<=preco_max){
                if(!compara_vetor_nos(vetor,*n,g->nos[i])){
                    (*n)++;
                    vetor=realloc(vetor,(*n)*sizeof(no_grafo*));
                    if(vetor==NULL){return NULL;}
                    vetor[*n-1]=g->nos[i];
                }
            }
        }
    }

    return vetor;
}

heap* dijstra_inicializa(grafo *g,no_grafo*origem){
    if(g==NULL || origem==NULL){return NULL;}

    heap *h;
    h=heap_nova(g->tamanho);
    if(h==NULL){return NULL;}

    int i;
    for(i=0;i<g->tamanho;i++){ 
        if(g->nos[i]==origem){
            g->nos[i]->p_acumulado=0;
        }
        else{
            g->nos[i]->p_acumulado=__DBL_MAX__;
        }
        g->nos[i]->anterior=NULL;
        g->nos[i]->dataatualizada=calloc(1,sizeof(data));

        if(!heap_insere(h,g->nos[i],g->nos[i]->p_acumulado)){return NULL;}
    }
    return h;
}

int nao_removido(no_grafo**vetor, int tamanho, no_grafo* no){
    if(vetor==NULL || tamanho<=0 || no==NULL){
        return -1;
    }

    int i;
    for(i=0;i<tamanho;i++){
        if(vetor[i]==no){
            return i;
        }
    }
    return -1;
}

int atualiza_heap(heap *h, no_grafo *no){
    if(h==NULL || no==NULL){return 0;}

    heap *aux;
    no_grafo *temp;
    aux=heap_nova(h->tamanho);
    if(aux==NULL){return 0;}

    while(1){
        temp=heap_remove(h);
        heap_insere(aux,temp,temp->p_acumulado);
        if(temp==no){
            break;
        }
        
    }
    
    while(aux->tamanho!=0){
        temp=heap_remove(aux);
        heap_insere(h,temp,temp->p_acumulado);
    }
    //printf("\n\n%f\n\n",h->elementos[1]->prioridade);
    heap_apaga(aux);
    return 1;
}

void dijstra_acaba(heap *h,grafo *g){
    if(h==NULL || g==NULL){return;}

    int i;
    for(i=0;i<g->tamanho;i++){
        free(g->nos[i]->dataatualizada);
        g->nos[i]->dataatualizada=NULL;
    }
    heap_apaga(h);
    return;
}


no_grafo **trajeto_mais_rapido(grafo *g, char *origem, char *destino, data partida, int *n)
{
    if(g==NULL || origem==NULL || destino==NULL || n==NULL){return NULL;}

    no_grafo *origem_no,*destino_no;
    origem_no=encontra_no(g,origem);
    if(origem_no==NULL){return NULL;}

    destino_no=encontra_no(g,destino);
    if(destino_no==NULL){return NULL;}

    *n=0;
    heap *h;
    h=dijstra_inicializa(g,origem_no);
    if(h==NULL){return NULL;}
    memcpy(origem_no->dataatualizada,&partida,sizeof(data));

    no_grafo**vetor;
    vetor=NULL;
    int tamanho=0,i;
    double diferenca,duracao_voo;
    //int pos_v,v;

    while(h->tamanho!=0){

        origem_no=heap_remove(h);

        if(origem_no==NULL){return NULL;}
        if(strcmp(origem_no->cidade,destino)==0){break;}
        
        if(origem_no->p_acumulado==__DBL_MAX__){dijstra_acaba(h,g);return NULL;}

        
        tamanho++;
        vetor=realloc(vetor,tamanho*sizeof(no_grafo*));
        if(vetor==NULL){return NULL;}
        vetor[tamanho-1]=origem_no;

        for(i=0;i<origem_no->tamanho;i++){
            diferenca=difftime(mktime(&origem_no->arestas[i]->partida),mktime(origem_no->dataatualizada));
            
            /*pos_v=nao_removido(vetor,tamanho,origem_no->arestas[i]->destino);
            if(pos_v!=-1){
                heap_insere(h,origem_no->arestas[i]->destino,origem_no->arestas[i]->destino->p_acumulado);
                for(v=pos_v;v<tamanho-1;v++){
                    vetor[v]=vetor[v+1];
                }
                tamanho--;
                vetor=realloc(vetor,tamanho*sizeof(no_grafo*));
            }*/

            if(diferenca>=0 && nao_removido(vetor,tamanho,origem_no->arestas[i]->destino)==-1){
                duracao_voo=difftime(mktime(&origem_no->arestas[i]->chegada),mktime(&origem_no->arestas[i]->partida));
                if(origem_no->arestas[i]->destino->p_acumulado>origem_no->p_acumulado+diferenca+duracao_voo){
                    
                    origem_no->arestas[i]->destino->p_acumulado=origem_no->p_acumulado+diferenca+duracao_voo;
                    origem_no->arestas[i]->destino->anterior=origem_no;
                    memcpy(origem_no->arestas[i]->destino->dataatualizada,origem_no->dataatualizada,sizeof(data));
                    origem_no->arestas[i]->destino->dataatualizada->tm_sec+=diferenca+duracao_voo;
                    mktime(origem_no->arestas[i]->destino->dataatualizada);
                    
                    if(!atualiza_heap(h,origem_no->arestas[i]->destino)){return NULL;}
                }
            }
        }
    }
    free(vetor);
    vetor=NULL;
    
    
    for(origem_no=destino_no;origem_no!=NULL;origem_no=origem_no->anterior){
        (*n)++;
    }
    vetor=malloc((*n)*sizeof(no_grafo*));
    origem_no=destino_no;
    for(i=*n-1;i>=0;i--){
        vetor[i]=origem_no;
        origem_no=origem_no->anterior;
    }
    dijstra_acaba(h,g);
    return vetor;
}

no_grafo **menos_transbordos(grafo *g, char *origem, char *destino, data partida, int *n)
{
    if(g==NULL || origem==NULL || destino==NULL || n==NULL){return NULL;}

    no_grafo *origem_no,*destino_no;
    origem_no=encontra_no(g,origem);
    if(origem_no==NULL){return NULL;}

    destino_no=encontra_no(g,destino);
    if(destino_no==NULL){return NULL;}

    *n=0;
    heap *h;
    h=dijstra_inicializa(g,origem_no);
    if(h==NULL){return NULL;}
    memcpy(origem_no->dataatualizada,&partida,sizeof(data));

    no_grafo**vetor;
    vetor=NULL;
    int tamanho=0,i;
    double diferenca,duracao_voo;
    int pos_v,v;

    while(h->tamanho!=0){

        origem_no=heap_remove(h);

        if(origem_no==NULL){return NULL;}
        if(strcmp(origem_no->cidade,destino)==0){break;}
        
        if(origem_no->p_acumulado==__DBL_MAX__){free(vetor);return NULL;}

        
        tamanho++;
        vetor=realloc(vetor,tamanho*sizeof(no_grafo*));
        if(vetor==NULL){return NULL;}
        vetor[tamanho-1]=origem_no;


        for(i=0;i<origem_no->tamanho;i++){
            diferenca=difftime(mktime(&origem_no->arestas[i]->partida),mktime(origem_no->dataatualizada));
            
            pos_v=nao_removido(vetor,tamanho,origem_no->arestas[i]->destino);
            if(pos_v!=-1){
                heap_insere(h,origem_no->arestas[i]->destino,origem_no->arestas[i]->destino->p_acumulado);
                for(v=pos_v;v<tamanho-1;v++){
                    vetor[v]=vetor[v+1];
                }
                tamanho--;
                vetor=realloc(vetor,tamanho*sizeof(no_grafo*));
            }
            
            if(diferenca>=0){
                if(origem_no->arestas[i]->destino->p_acumulado>origem_no->p_acumulado+1){
                    duracao_voo=difftime(mktime(&origem_no->arestas[i]->chegada),mktime(&origem_no->arestas[i]->partida));
                    origem_no->arestas[i]->destino->p_acumulado=origem_no->p_acumulado+1;
                    origem_no->arestas[i]->destino->anterior=origem_no;
                    memcpy(origem_no->arestas[i]->destino->dataatualizada,origem_no->dataatualizada,sizeof(data));
                    origem_no->arestas[i]->destino->dataatualizada->tm_sec+=diferenca+duracao_voo;
                    mktime(origem_no->arestas[i]->destino->dataatualizada);
                    
                    if(!atualiza_heap(h,origem_no->arestas[i]->destino)){return NULL;}
                }
            }
        }
    }
    free(vetor);
    vetor=NULL;
    
    
    for(origem_no=destino_no;origem_no!=NULL;origem_no=origem_no->anterior){
        (*n)++;
    }
    vetor=malloc((*n)*sizeof(no_grafo*));
    origem_no=destino_no;
    for(i=*n-1;i>=0;i--){
        vetor[i]=origem_no;
        origem_no=origem_no->anterior;
    }
    dijstra_acaba(h,g);
    return vetor;
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
    char linha[151],*token,*codigo;
    codigo=NULL;
    int lugares,aresta_i;
    no_grafo *encontrado;
    aresta_grafo** vetor;
    *n=0;
    vetor=NULL;

    while(fgets(linha,150,f)!=NULL){
        token=strstr(linha,"\n");
        if(token!=NULL){*token='\0';}

        token=strtok(linha,",");
        if(token==NULL){continue;}
        codigo=realloc(codigo,(strlen(token)+1)*sizeof(char));
        strcpy(codigo,token);

        token=strtok(NULL,",");
        if(token==NULL){continue;}
        lugares=atoi(token);
        
        encontrado=encontra_voo(g,codigo,&aresta_i);
        encontrado->arestas[aresta_i]->lugares=lugares;

        if(lugares==0){
            (*n)++;
            vetor=realloc(vetor,(*n)*sizeof(aresta_grafo*));
            if(vetor==NULL){free(codigo);return NULL;}
            vetor[*n-1]=encontrado->arestas[aresta_i];
            if(!retira_vetor_aresta(encontrado,aresta_i)){free(codigo);return NULL;}
        }

    }
    fclose(f);
    free(codigo);
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
