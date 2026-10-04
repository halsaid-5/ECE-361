CC = gcc
CFLAGS = -std=c11 -Wall -Wextra

OBJS = bits.o status.o

all: $(OBJS)

bits.o: bits.c bits.h
	$(CC) $(CFLAGS) -c bits.c

status.o: status.c status.h bits.h
	$(CC) $(CFLAGS) -c status.c

tests/test_bits: tests/test_bits.c $(OBJS)
	$(CC) $(CFLAGS) -I. tests/test_bits.c $(OBJS) -o tests/test_bits

test: tests/test_bits
	./tests/test_bits

clean:
	rm -f $(OBJS) tests/test_bits