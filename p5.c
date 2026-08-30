/*
Question:
Write a MPI Program to demonstration of MPI_Send and MPI_Recv.
*/

#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    int rank, size;
    MPI_Status status;

    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get current process rank and total number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Process 0 sends a message to all other processes
    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            char message[100];

            sprintf(message, "Hello from process 0 to process %d", i);

            MPI_Send(
                message,
                strlen(message) + 1,
                MPI_CHAR,
                i,
                0,
                MPI_COMM_WORLD
            );

            printf("Process 0 sent message to process %d\n", i);
            fflush(stdout);
        }
    } else {
        // All other processes receive the message from process 0
        char recv_buf[100];

        MPI_Recv(
            recv_buf,
            100,
            MPI_CHAR,
            0,
            0,
            MPI_COMM_WORLD,
            &status
        );

        printf("Process %d received message: %s\n", rank, recv_buf);
        fflush(stdout);
    }

    // Finalize MPI
    MPI_Finalize();

    return 0;
}

/*
output :- 
mpicc p5.c -o p5
mpirun -np 6 ./p5   --> here 6 means 0,1,2,3,4,5

Process 0 sent message to process 1
Process 0 sent message to process 2
Process 0 sent message to process 3
Process 0 sent message to process 4
Process 0 sent message to process 5
Process 1 received message: Hello from process 0 to process 1
Process 2 received message: Hello from process 0 to process 2
Process 3 received message: Hello from process 0 to process 3
Process 4 received message: Hello from process 0 to process 4
Process 5 received message: Hello from process 0 to process 5

*/
