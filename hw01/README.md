# ECE 361 - Homework 01

## Description

This homework practices bit manipulation in C.

The program includes functions to:
- Print a value in binary.
- Extract a field of bits.
- Set a field of bits.
- Sign extend a value.
- Unpack a 16-bit status word.

## Files

- `bits.c` - Bit manipulation functions.
- `bits.h` - Function declarations.
- `status.c` - Unpacks the status word.
- `status.h` - Defines the status structure.
- `tests/test_bits.c` - Tests the functions.
- `Makefile` - Builds and tests the program.

## Build and Test

Run:

```bash
make
make test