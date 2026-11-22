# Reproduce original crash (before fixing search)

The assignment asks for a real sanitizer report **before** fixing the original search.
The file `tests/buggy_search_demo.c` is a separate experiment and is not for submission.

On macOS, from `hw08/`, run:

```sh
cc -std=c11 -g -fsanitize=address,undefined -fno-omit-frame-pointer -o /tmp/hw08_bug tests/buggy_search_demo.c
/tmp/hw08_bug
```

The program is **supposed** to crash. Copy the first actual sanitizer report line into `README.md`.
Then run `make memcheck` on the fixed implementation; it should pass.

The assignment specifically says to port and test the faulty search first. This standalone
experiment demonstrates the same original bug, but check with your instructor whether
this workflow meets the requested test-before-fix process.
