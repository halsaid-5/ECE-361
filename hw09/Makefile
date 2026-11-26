CC = cc
CFLAGS = -std=c11 -Wall -Wextra -Werror -g
SANFLAGS = -fsanitize=address,undefined -fno-omit-frame-pointer

.PHONY: all test memcheck clean

all: tests/test_ht

tests/test_ht: tests/test_ht.c ht.c ht.h
	$(CC) $(CFLAGS) -o $@ tests/test_ht.c ht.c

test: tests/test_ht
	./tests/test_ht

memcheck:
	$(MAKE) clean
	$(MAKE) CFLAGS="$(CFLAGS) $(SANFLAGS)" test

clean:
	rm -f tests/test_ht *.o tests/*.o
