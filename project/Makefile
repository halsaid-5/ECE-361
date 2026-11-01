CC = gcc
CFLAGS = -std=c11 -Wall -Wextra
LDLIBS = -lm
SRC = main.c fsm.c sensor.c store.c aux.c report.c status.c iom361_r4.c ../hw01/bits.c
OBJ = $(SRC:.c=.o)
.PHONY: all test clean
all: gate
gate: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDLIBS)
tests/unit: tests/unit.c fsm.c sensor.c store.c aux.c report.c status.c iom361_r4.c ../hw01/bits.c
	$(CC) $(CFLAGS) -I. -o $@ $^ $(LDLIBS)
test: gate tests/unit
	@python3 tests/run_tests.py
clean:
	rm -f $(OBJ) gate tests/unit
