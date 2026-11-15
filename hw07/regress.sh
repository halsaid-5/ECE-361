#!/bin/sh
set -eu
for input in inputs/*.txt; do
    name=$(basename "$input" .txt)
    actual=$(mktemp)
    trap 'rm -f "$actual"' EXIT HUP INT TERM
    status=0
    ./balance < "$input" > "$actual" || status=$?
    expected_status=$(cat "expected/$name.status")
    if [ "$status" -ne "$expected_status" ] || ! diff -u "expected/$name.txt" "$actual"; then
        echo "FAIL regression: $name (status $status; expected $expected_status)"
        exit 1
    fi
    echo "PASS regression: $name"
    rm -f "$actual"
    trap - EXIT HUP INT TERM
done
