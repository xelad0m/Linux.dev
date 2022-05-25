CC=gcc
CFLAGS=-Wall -fPIC -ldl

all: solution 

solution: solution.c
	$(CC) $< $(CFLAGS) -o $@


clean:
	-rm *.o solution 2>/dev/null
