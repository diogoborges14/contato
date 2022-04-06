# Variávies
CC = gcc
CFLAGS = -pedantic-errors -Wall `pkg-config --cflags gtk+-3.0`
LFLAGS = `pkg-config --libs gtk+-3.0`

# Regra : dependências
all: dynamicList.o contatos.o
	$(CC) $(LFLAGS) contatos.o include/dynamicList.o -o contatos

contatos.o: contatos.c
	$(CC) $(CFLAGS) -c contatos.c -o contatos.o

dynamicList.o: include/dynamicList.c
	$(CC) $(CFLAGS) -c include/dynamicList.c -o include/dynamicList.o

clean:
	rm *.o include/*.o contatos

run:
	./contatos

debug:
	make CFLAGS+=-g