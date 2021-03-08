#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*O programa corre na maior parte das vezes se for retirado a linha 21 dando o erro "Segmentation fault(core dumped)" raramente, porem com a linha 21 presente apenas corre bem a extrair e imprimir o primeiro link dando o mesmo erro a seguir*/

int main(){
    FILE *f; //inicia a variável que aponta para o ficheiro
    char link[200], beg[]="<a href=\"", *ref,pagina[200],end[]="\"", end2[]="</a>";
    f=fopen("pagina.html","r"); //abre o ficheiro
    
    while (fgets(link,200,f) != NULL){  //enquanto obtiver uma linha do ficheiro granda em link e faz:
        ref=strstr(link,beg); //guarda em ref o endereço de memória em que <a heref=" aparece na linha obtida
        if (ref == NULL)  //se o <a heref=" nao estiver presente em link ignora as próximas instruções
            continue;
        memmove(link,ref+9,strlen(ref+9)); //ref aponta para o endereço de memoria do inicio em que aparece <a heref=", como <a heref=" tem 9 caracteres, ref+9 irá apontar para o fim de <a heref=", ou seja a string link terá uma copia da própria string a partir do endereço ref+9 ate ao fim da string link, eliminando da string <a heref=" e tudo o resto que tiver para trás     
        memmove(pagina,link, strlen(link)); //copia a string link para a string pagina
	
        *strstr(link,end)='\0'; //o final do link a obter esta marcado com o uso de ", ou seja strstr(link,end) será o endereço de memoria onde esta localizado " na string e muda o seu valor para \0 provocando assim um fim prematuro na impressão da string imprimindo apenas o desejado     
        memmove(pagina,strstr(pagina,end)+2, strlen(strstr(pagina,end)+2)); //o inicio do titulo da pagina segue-se 2 caracteres depois do final do link a obter (quando aparecem "), ou seja strstr(pagina,end)+2 será o endereço de memoria na string pagina onde começa o titulo da pagina e irá copiar a string pagina apartir dai ate ao fim da string pagina, eliminando assim da string pagina tudo o que estiver para tras do titulo
        *strstr(pagina,end2)='\0'; //o final do titulo esta marcado com o uso de </a>, ou seja strstr(pagina,end2) será o primeiro endereço de memoria onde esta localizado </a> na string pagina e muda o seu valor para \0 provocando assim um fim prematuro na impressão da string imprimindo apenas o desejado

	printf("%s - %s\n",pagina,link); //imprime o que foi pedido
    }
    fclose(f); //fecha o ficheiro
    

    return 0;
}
