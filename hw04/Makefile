
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -I.

all: events

events: events.o tally.o
	$(CC) $(CFLAGS) events.o tally.o -o events

events.o: events.c tally.h
	$(CC) $(CFLAGS) -c events.c

tally.o: tally.c tally.h
	$(CC) $(CFLAGS) -c tally.c

test_tally: tests/test_tally.c tally.o tally.h
	$(CC) $(CFLAGS) tests/test_tally.c tally.o -o test_tally

test: test_tally
	./test_tally

clean:
	rm -f events test_tally events.o tally.o

.PHONY: all test clean
