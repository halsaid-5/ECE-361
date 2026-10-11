CC = gcc
CFLAGS = -std=c11 -Wall -Wextra

readings: main.o reading.o stats.o histogram.o
	$(CC) $(CFLAGS) main.o reading.o stats.o histogram.o -o readings

main.o: main.c reading.h stats.h histogram.h
	$(CC) $(CFLAGS) -c main.c

reading.o: reading.c reading.h
	$(CC) $(CFLAGS) -c reading.c

stats.o: stats.c stats.h
	$(CC) $(CFLAGS) -c stats.c

histogram.o: histogram.c histogram.h
	$(CC) $(CFLAGS) -c histogram.c


test_stats: tests/test_stats.c stats.c stats.h
	$(CC) $(CFLAGS) tests/test_stats.c stats.c -o test_stats

test: readings test_stats
	./test_stats
	sh regress.sh

clean:
	rm -f readings test_stats *.o

.PHONY: test clean

