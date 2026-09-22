/*
Write a MPI Program to demonstrate the Broadcast operation.
*/

#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int rank, size;
    int number;

    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get rank and number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Process 0 initializes the number
    if (rank == 0) {
        number = 42;
        printf("Process 0 is broadcasting number %d\n", number);
    }

    // Broadcast number to all processes
    MPI_Bcast(&number, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Print received number
    printf("Process %d received number %d\n", rank, number);

    // Finalize MPI
    MPI_Finalize();

    return 0;
}




/*
output:-
mpicc p7.c -o p7
mpirun --oversubscribe -np 4 ./p7      ---> Run with 4 processes



Process 0 is broadcasting number 42
Process 1 received number 42
Process 0 received number 42
Process 2 received number 42
Process 3 received number 42

*/
