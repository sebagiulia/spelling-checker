FILES.O = structures/glist.o structures/tablahash.o words.o filefunctions.o mainfunctions.o techniques.o main.c

FLAGS = -g -Wall -Wextra -std=c99

CC = gcc

EXE.NAME = main

glist.o: structures/glist.c
	$(CC) $(FLAGS) -c glist.c

tablahash.o: structures/tablahash.c
	$(CC) $(FLAGS) -c tablahash.c

words.o: words.c
	$(CC) $(FLAGS) -c words.c

filefunctions.o: filefunctions.c
	$(CC) $(FLAGS) -c filefunctions.c

mainfunctions.o: mainfunctions.c
	$(CC) $(FLAGS) -c mainfunctions.c

techniques.o: techniques.c
	$(CC) $(FLAGS) -c techniques.c

main.o: main.c
	$(CC) $(FLAGS) -c main.c

program: $(FILES.O)
	$(CC) -o $(EXE.NAME) $(FILES.O)

clean:
	rm *.o
	rm */*.o
