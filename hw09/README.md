# ECE 361 - Homework 9

This project implements a hash table with separate chaining. Each bucket holds a linked list, and each different key has a count.

## Build and test

From the `hw09` folder, run:

```sh
make
make test
make memcheck
make clean
```

`make test` runs the unit tests. `make memcheck` rebuilds the tests with AddressSanitizer and UndefinedBehaviorSanitizer.

## Why the bucket counts matter

With 1000 buckets, keys 10, 20, ..., 10000 collide in groups of 10 because the keys are multiples of 10, so the longest chain is 10 instead of 1. With 1009 buckets, these 1000 different keys land in different buckets, so the longest chain is 1.
