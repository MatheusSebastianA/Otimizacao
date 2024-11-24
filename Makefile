CFLAGS = -Wall -std=c99  # flags de compilacao

CC = gcc

# arquivos-objeto
	objects = producao.o lib_producao.o

producao: producao.o lib_producao.o
	$(CC) -o producao producao.o lib_producao.o

lib_producao.o: lib_producao.c
	$(CC) -c $(CFLAGS)  lib_producao.c

producao.o: producao.c
	$(CC) -c $(CFLAGS) producao.c

clean:
	rm -f $(objects) 

purge:
	rm -f producao
