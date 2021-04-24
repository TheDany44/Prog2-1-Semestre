prob1: fila.o lista.o prob1.c
	clang prob1.c fila.o lista.o -o prob1

fila.o:	fila.c fila.h
	clang fila.c -c 

lista.o: lista.c lista.h
	clang lista.c -c 

clean: 
	rm lista.o
	rm fila.o
	rm prob1