CC = gcc
CFLAGS = -Wall -ansi -pedantic
MAIN = Percemaille.c

all : main exec

main : 
	$(CC) $(CFLAGS) -c $(MAIN) -o Percemaille.o

exec : Percemaille.o
	$(CC) $(CFLAGS) -o main.exe main.c Percemaille.o

run : main.exe
	./main.exe

library : Percemaille.o
	ar rcs percemaille.lib Percemaille.o
