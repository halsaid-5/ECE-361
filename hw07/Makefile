CC = cc
CFLAGS = -std=c11 -Wall -Wextra -Werror -g
SANFLAGS = -fsanitize=address,undefined -fno-omit-frame-pointer

.PHONY: all test memcheck clean
all: balance
balance: balance.o istack.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ balance.o istack.o
balance.o: balance.c istack.h
	$(CC) $(CFLAGS) -c balance.c
istack.o: istack.c istack.h
	$(CC) $(CFLAGS) -c istack.c
tests/test_istack: tests/test_istack.c istack.c istack.h
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ tests/test_istack.c istack.c
test: balance tests/test_istack
	./tests/test_istack
	sh regress.sh
memcheck:
	$(MAKE) clean
	$(MAKE) CFLAGS="$(CFLAGS) $(SANFLAGS)" LDFLAGS="$(SANFLAGS)" test
clean:
	rm -f balance balance.o istack.o tests/test_istack
