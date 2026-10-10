# HW02 - Sensor Readings
## Description
This program reads sensor data from a file. It calculates the minimum, maximum, and mean for temperature and humidity. It also finds the longest run above a temperature threshold and prints a histogram.

## How to Compile
```bash
make
```

## How to Run
```bash
./readings < data/normal.txt
```

To use a different temperature threshold:
```bash
./readings 25 < data/normal.txt
```

## How to Test
```bash
make test
```

To run the regression tests:
```bash
./regress.sh
```

## Results
The program passed the statistics tests and all three regression tests: normal, edge, and empty.