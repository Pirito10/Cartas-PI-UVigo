CC	=gcc -Wall

all: letters

inout.o: inout.c inout.h
	$(CC) -c inout.c

operation.o: operation.c operation.h
	$(CC) -c operation.c

letters: letters.c inout.o operation.o
	$(CC) inout.o operation.o letters.c -o letters

clean:
	rm -f letters *.o *~ *.bak abonados.txt mensajes.txt