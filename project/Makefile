
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra

SRC = main.c fsm.c sensor.c store.c aux.c report.c iom361_r4.c ../hw01/bits.c
OBJ = main.o fsm.o sensor.o store.o aux.o report.o iom361_r4.o bits.o

all: gate

gate: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o gate

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

main.o: iom361_r4.h
fsm.o: fsm.h
sensor.o: sensor.h
store.o: store.h
aux.o: aux.h
report.o: report.h
iom361_r4.o: iom361_r4.h
bits.o: ../hw01/bits.c ../hw01/bits.h
	$(CC) $(CFLAGS) -c ../hw01/bits.c -o bits.o

test: gate
	@./gate

clean:
	rm -f $(OBJ) gate parking_gate

.PHONY: all test clean
