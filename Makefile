# Variávies
CC = gcc
CFLAGS = -pedantic-errors -Wall `pkg-config --cflags gtk+-3.0`
LFLAGS = `pkg-config --libs gtk+-3.0`

# Regra : dependências
all: linkedContactList.o contatos.o
	$(CC) $(LFLAGS) $(DEBUG) contatos.o include/linkedContactList.o -o contatos

contatos.o: contatos.c
	$(CC) $(CFLAGS) $(DEBUG) -c contatos.c -o contatos.o

linkedContactList.o: include/linkedContactList.c
	$(CC) $(CFLAGS) $(DEBUG) -c include/linkedContactList.c -o include/linkedContactList.o

clean:
	rm *.o include/*.o contatos

run:
	./contatos

debug:
	make DEBUG=-g