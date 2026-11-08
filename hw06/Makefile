CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror
LDLIBS = -lm
OBJS = main.o sensor.o panel.o scenario.o iom361_r4.o

.PHONY: all test clean
all: replay

replay: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDLIBS)

main.o: main.c sensor.h panel.h scenario.h iom361_r4.h
sensor.o: sensor.c sensor.h iom361_r4.h
panel.o: panel.c panel.h iom361_r4.h
scenario.o: scenario.c scenario.h
iom361_r4.o: iom361_r4.c iom361_r4.h

tests/test_hw06: tests/test_hw06.c sensor.c panel.c scenario.c iom361_r4.c sensor.h panel.h scenario.h iom361_r4.h
	$(CC) $(CFLAGS) -I. -o $@ tests/test_hw06.c sensor.c panel.c scenario.c iom361_r4.c $(LDLIBS)

test: replay tests/test_hw06
	./tests/test_hw06
	sh regress.sh

clean:
	rm -f $(OBJS) replay tests/test_hw06
