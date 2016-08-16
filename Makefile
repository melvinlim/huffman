CC=gcc
CFLAGS=-O0 -I. -g
DEPS = heap.h stack.h encode.h
OBJ = heap.o stack.o encode.o test.o
TARGS = test

all: $(TARGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o *~ a.out $(TARGS)
