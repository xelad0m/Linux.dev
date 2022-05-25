CC=gcc

all: main

main: fcount.o main.o			# $^ all src, $< 1st src
	$(CC) $^ -o $@

main.o: main.c
	$(CC) -c $^ -o $@

fcount.o: fcount.c
	$(CC) -c $^ -o $@

clean:
	-rm *.o main 2>/dev/null
