
#!/bin/sh

set -e

make readings

for name in normal edge empty
do
    echo "Testing $name..."
    ./readings < "data/$name.txt" | diff - "expected/$name.txt"
done

echo "All regression tests passed!"
