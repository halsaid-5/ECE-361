# ECE 361 Parking Gate - Beginner C implementation

This folder is a **separate copy**, not a change to your GitHub repository.

## Use on Mac
1. Make a backup of your current `ECE-361/project` folder.
2. Copy the contents of this `project` folder into your existing `ECE-361/project` folder.
3. Keep your original `iom361_r4.c` and `iom361_r4.h` if you prefer. The copies here are from the provided iom361_r4 archive, unchanged.
4. Keep `ECE-361/hw01/bits.c` and `bits.h` from your own HW1. The included copies are compatible alternatives.
5. Run:

```sh
cd ~/ECE-361/project
make clean
make
make test
./gate scenarios/normal.txt
./gate scenarios/report.txt --report
```

Before submission, read `SPEC.md`, update `AI_USAGE.md` to reflect your own use, and make sure you can explain the code. The course includes an individual final exam about your project.
