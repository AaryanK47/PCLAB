/*
Write a MPI Program demonstration of MPI_Scatter and MPI_Gather.
*/

#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int rank, size;
    int data[100];
    int recv_value;
    int gathered[100];

    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get rank and size
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Only rank 0 initializes data
    if (rank == 0) {
        for (int i = 0; i < size; i++) {
            data[i] = i * 10;
        }

        printf("Process 0 initialized data: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", data[i]);
        }
        printf("\n");
    }

    // SCATTER
    MPI_Scatter(data, 1, MPI_INT,
                &recv_value, 1, MPI_INT,
                0, MPI_COMM_WORLD);

    printf("Process %d received value %d from Scatter\n",
           rank, recv_value);

    // Each process modifies its value
    recv_value += rank;

    // GATHER
    MPI_Gather(&recv_value, 1, MPI_INT,
               gathered, 1, MPI_INT,
               0, MPI_COMM_WORLD);

    // Only rank 0 displays gathered results
    if (rank == 0) {
        printf("Process 0 gathered data: ");

        for (int i = 0; i < size; i++) {
            printf("%d ", gathered[i]);
        }

        printf("\n");
    }

    // Finalize
    MPI_Finalize();

    return 0;
}





/*
output:-
mpicc p8.c -o p8
mpirun --oversubscribe -np 4 ./p8             --> Run with 4 processes


Process 0 initialized data: 0 10 20 30 
Process 0 received value 0 from Scatter
Process 2 received value 20 from Scatter
Process 3 received value 30 from Scatter
Process 1 received value 10 from Scatter
Process 0 gathered data: 0 11 22 33 

*/
