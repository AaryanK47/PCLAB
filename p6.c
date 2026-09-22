/* 
Write an MPI program to demonstrate deadlock using point-to-point communication 
and avoidance of deadlock by altering the call sequence.
*/

#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int rank, send_data, recv_data;
    MPI_Status status;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Data based on rank
    send_data = (rank == 0) ? 100 : 200;

    printf("Process %d: Before Sendrecv with data %d\n", rank, send_data);
    fflush(stdout);

    // Avoid deadlock using MPI_Sendrecv
    if (rank == 0) {
        MPI_Sendrecv(&send_data, 1, MPI_INT, 1, 0,
                     &recv_data, 1, MPI_INT, 1, 0,
                     MPI_COMM_WORLD, &status);
    }
    else if (rank == 1) {
        MPI_Sendrecv(&send_data, 1, MPI_INT, 0, 0,
                     &recv_data, 1, MPI_INT, 0, 0,
                     MPI_COMM_WORLD, &status);
    }

    printf("Process %d: After Sendrecv, received %d\n", rank, recv_data);
    fflush(stdout);

    MPI_Finalize();
    return 0;
}


/*
output :- 
mpicc p6.c -o p6
mpirun -np 2 ./p6  --> run with 2 process
            OR
mpirun --allow-run-as-root -np 2 ./p6  --> run with 2 process



Process 1: Before Sendrecv with data 200
Process 0: Before Sendrecv with data 100
Process 0: After Sendrecv, received 200
Process 1: After Sendrecv, received 100
*/
