# C Programs

## THESE COMMANDS ARE FOR UBUNTU ISO ---> INSIDE VIRTUAL BOX


To execute a C program, open the terminal and navigate to the directory containing the `.c` file.

---

# Program 1

```bash
gcc -fopenmp p1.c -o p1
./p1
```

---

# Program 2

```bash
gcc -fopenmp p2.c -o p2
./p2
```

---

# Program 3

```bash
gcc -fopenmp p3.c -o p3
./p3
```

---

# Program 4

```bash
gcc -fopenmp p4.c -o p4 -lm
./p4
```

`-lm` is required because Program 4 uses the `sqrt()` mathematical function.

---

# Program 5

```bash
mpicc p5.c -o p5
mpirun -np 6 ./p5
```

`-np 6` runs the MPI program using 6 processes.

---
