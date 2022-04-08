# Variávies
CC = gcc
CFLAGS = -pedantic-errors -Wall `pkg-config --cflags gtk+-3.0`
LFLAGS = `pkg-config --libs gtk+-3.0`

# Regra : dependências
all: dynamicList.o contatos.o
	$(CC) $(LFLAGS) $(DEBUG) contatos.o include/dynamicList.o -o contatos

contatos.o: contatos.c
	$(CC) $(CFLAGS) $(DEBUG) -c contatos.c -o contatos.o

dynamicList.o: include/dynamicList.c
	$(CC) $(CFLAGS) $(DEBUG) -c include/dynamicList.c -o include/dynamicList.o

clean:
	rm *.o include/*.o contatos

run:
	./contatos

debug:
	make DEBUG=-g