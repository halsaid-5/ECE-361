CC = gcc
CFLAGS = -std=c11 -Wall -Wextra

SRC = main.c fsm.c sensor.c store.c aux.c report.c iom361_r4.c

all: parking_gate

parking_gate: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o parking_gate

clean:
	rm -f parking_gate

