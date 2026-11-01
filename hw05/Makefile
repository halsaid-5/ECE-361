CC = gcc
CFLAGS = -std=c11 -Wall -Wextra

all: lock

lock: main.o lock.o
	$(CC) $(CFLAGS) main.o lock.o -o lock

main.o: main.c lock.h
	$(CC) $(CFLAGS) -c main.c

lock.o: lock.c lock.h
	$(CC) $(CFLAGS) -c lock.c

test_lock: tests/test_lock.c lock.c lock.h
	$(CC) $(CFLAGS) -I. tests/test_lock.c lock.c -o test_lock

test_check: tests/test_check.c check.c check.h lock.c lock.h
	$(CC) $(CFLAGS) -I. tests/test_check.c check.c lock.c -o test_check

test: test_lock test_check
	./test_lock
	./test_check

clean:
	rm -f lock test_lock test_check *.o

.PHONY: all test clean
