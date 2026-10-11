CC = gcc
CFLAGS = -std=c11 -Wall -Wextra

SRC = main.c fsm.c sensor.c store.c aux.c report.c iom361_r4.c
OBJ = $(SRC:.c=.o)

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

test: gate
	@./gate

clean:
	rm -f $(OBJ) gate parking_gate

.PHONY: all test clean
