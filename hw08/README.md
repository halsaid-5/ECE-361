# ECE 361 – Homework 8

## Build and test

```sh
make clean
make
make test
make memcheck
```

## Part 2 – Crash before the fix

The original `search()` uses `while(current->data != data)` before checking whether `current` is `NULL`. Calling search on an empty tree causes a null-pointer dereference. The original `main()` only searches a populated tree, so it does not exercise this case.

**Before submission:** Run the original-style buggy search under `make memcheck` using the empty-tree test. Copy the **actual first AddressSanitizer/UndefinedBehaviorSanitizer report line** here, and note the triggering test. Do not invent the report.

- Triggering test: search for key `3` in an empty tree.
- Actual first report line: tests/buggy_search_demo.c:9:21: runtime error: member access within null pointer of type 'struct node'
- Fix: `bst_contains` checks `current != NULL` before accessing `current->data`.

## Part 3 – Insertion order

Run these on a system with `seq` and `sort -R`:

```sh
seq 1 1023 | ./treestats
seq 1 1023 | sort -R | ./treestats
```

- Increasing-order output: n 1023, height 1023
- Shuffled-order output: n 1023, height 23

Increasing order creates a long one-sided tree, so its height and worst-case search visits grow. Shuffled order usually creates a shorter tree, so searches generally need fewer visits.

## Program examples

```sh
printf '27 14 35 10 19 31 42\n' | ./treestats
# n 7, height 3
printf '' | ./treestats
# empty tree
printf '1 2 3 4 nope\n' | ./treestats
# not a number after 4 values (exit 1)
```
