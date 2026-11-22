CC = cc
CFLAGS = -std=c11 -Wall -Wextra -Werror -g
SANFLAGS = -fsanitize=address,undefined -fno-omit-frame-pointer

.PHONY: all test memcheck clean
all: treestats

treestats: treestats.c bst.c bst.h
	$(CC) $(CFLAGS) -o $@ treestats.c bst.c

tests/test_bst: tests/test_bst.c bst.c bst.h
	$(CC) $(CFLAGS) -o $@ tests/test_bst.c bst.c

test: treestats tests/test_bst
	./tests/test_bst
	sh regress.sh

memcheck:
	$(MAKE) clean
	$(MAKE) CFLAGS="$(CFLAGS) $(SANFLAGS)" test

clean:
	rm -f treestats tests/test_bst *.o tests/*.o
