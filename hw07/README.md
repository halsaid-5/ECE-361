# ECE 361 - Homework 7

## Build and test

```sh
make clean
make
make test
make memcheck
make clean
```

Run bracket checker with `./balance < inputs/balanced.txt`. The stack starts with capacity 8 and doubles when full.

## Part 4 - Deliberate memory bugs

**Complete this section yourself after actually running each experiment. Do not submit invented sanitizer reports.**

1. **Double Free**

   First report line:
   `==80171==ERROR: AddressSanitizer: heap-use-after-free`

   I destroyed the same stack twice. The second call tried
   to use memory that was already freed. AddressSanitizer
   detected the error.

   I tested this in a separate file, so the original code
   was not changed.
2. **Use After Free**

   First report line:
   `==80802==ERROR: AddressSanitizer: heap-use-after-free`

   I destroyed the stack and then tried to push the number 3 into it. AddressSanitizer detected that the program was using memory after it was freed.

   I tested this in a separate file, so the original code was not changed.
3. **Memory Leak**

   I created a stack and intentionally did not call `istack_destroy(s)`.

   I tested the program using the macOS `leaks` tool. The report showed:

   `0 leaks for 0 total leaked bytes.`

   I also tried AddressSanitizer, but it reported:

   `AddressSanitizer: detect_leaks is not supported on this platform.`

   The memory leak was not detected by these tools on my Mac. The test was done in a separate file, so the original code was not changed.

**After restoring correct code, run `make clean && make memcheck` and verify it passes.**

## Results from my computer

Fill in the actual test and memory-check results before submitting.
