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


# Program 6

```bash
mpicc p6.c -o p6
mpirun --oversubscribe -np 2 ./p6
```
`-np 2` runs the MPI program using 2 processes.

This program demonstrates deadlock avoidance using MPI_Sendrecv().

---

# Program 7

```bash
mpicc p7.c -o p7
mpirun --oversubscribe -np 4 ./p7
```
`-np 4` runs the MPI program using 4 processes.

This program demonstrates the MPI Broadcast operation using MPI_Bcast().

---


# Program 8

```bash
mpicc p8.c -o p8
mpirun --oversubscribe -np 4 ./p8
```
`-np 4` runs the MPI program using 4 processes.

This program demonstrates MPI_Scatter and MPI_Gather.

---

# Program 9

```bash
mpicc p9.c -o p9
mpirun --oversubscribe -np 2 ./p9
```
`-np 2` runs the MPI program using 2 processes.

This program demonstrates MPI_Reduce and MPI_Allreduce using:

`MPI_SUM`
`MPI_PROD`
`MPI_MAX`
`MPI_MIN`

---

