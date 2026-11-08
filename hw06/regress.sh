#!/bin/sh
set -eu
for name in basic weather; do
    ./replay "scenarios/$name.txt" > "expected/$name.actual"
    if diff -u "expected/$name.txt" "expected/$name.actual"; then
        echo "PASS regression: $name"
    else
        rm -f "expected/$name.actual"
        exit 1
    fi
    rm -f "expected/$name.actual"
done
