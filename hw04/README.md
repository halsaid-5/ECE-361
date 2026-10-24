# ECE 361 - Homework 4

## Description
This program uses a tally to count how many times each name appears. It stores up to 16 different names and supports up to 4 tallies.

## Build and Run
Open the terminal inside the `hw04` folder.

Build the program:
```bash
make
```

Run the program:
```bash
./events < data/door.txt
```

Run the tests:
```bash
make test
```

Remove compiled files:
```bash
make clean
```

## Testing
I tested the tally functions using `test_tally.c`. The tests check adding names, counting names, invalid inputs, and full tallies.

## Opaque Type
The `tally_t` type is opaque because its structure is hidden in `tally.c`. Other files can use the functions in `tally.h`, but they cannot directly access the data inside the tally. This is useful because it protects the data and prevents other files from changing it incorrectly.

## Compiler Error

I tried to access `t->n` from `test_tally.c`.

The compiler showed this error:

```text
error: incomplete definition of type 'tally_t'
```

This happened because `tally_t` is an opaque type. Its internal fields are hidden from other files.