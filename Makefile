CC=gcc
CFLAGS=-O3 -I.
DEPS = heap.h
OBJ = heap.o test.o
TARGS = test

all: $(TARGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o *~ a.out $(TARGS)
