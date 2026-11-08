# ECE 361 Homework 6

This is the separate `hw06/` assignment, not the parking gate `project/`.

## Build

```sh
cd ~/ECE-361/hw06
make
```

## Run

```sh
./replay scenarios/basic.txt
./replay scenarios/weather.txt
```

## Test

```sh
make test
```

## Clean

```sh
make clean
```

The replay program toggles one LED for each new switch press. It reads the sensor and switches through iom361 registers and prints one line for each tick in UTC.
