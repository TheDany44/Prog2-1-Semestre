teste: teste_armazem.c fila_contentores.o armazem.o contentor.o fila_contentores.o pilha_contentores.o
	clang teste_armazem.c armazem.o contentor.o fila_contentores.o pilha_contentores.o -o teste

fila_contentores.o: fila_contentores.h fila_contentores.c 
	clang fila_contentores.c -c 

armazem.o: armazem.c armazem.h
	clang armazem.c -c

contentor.o: contentor.c contentor.h
	clang contentor.c -c 

pilha_contentores.o: pilha_contentores.c pilha_contentores.h
	clang pilha_contentores.c -c 

clean: 
	rm pilha_contentores.o
	rm contentor.o
	rm armazem.o 
	rm fila_contentores.o
	rm teste