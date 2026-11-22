#!/bin/sh
set -eu
check() {
  name=$1
  expected=$2
  input=$3
  output=$(printf '%s' "$input" | ./treestats)
  if [ "$output" = "$expected" ]; then
    echo "PASS regression: $name"
  else
    echo "FAIL regression: $name (got: $output)"
    exit 1
  fi
}
check empty 'empty tree' ''
check sample 'n 7, height 3' '27 14 35 10 19 31 42'
check increasing 'n 5, height 5' '1 2 3 4 5'
set +e
output=$(printf '1 2 3 4 nope\n' | ./treestats)
status=$?
set -e
if [ "$status" -eq 1 ] && [ "$output" = 'not a number after 4 values' ]; then
  echo 'PASS regression: invalid input'
else
  echo "FAIL regression: invalid input (status $status, output $output)"
  exit 1
fi
