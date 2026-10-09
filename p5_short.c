
/*
Write an MPI program to demonstrate MPI_Send and MPI_Recv.
*/

#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int rank, size;
    char msg[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            sprintf(msg, "Hello from process 0 to process %d", i);
            MPI_Send(msg, strlen(msg)+1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
            printf("Process 0 sent message to process %d\n", i);
        }
    } else {
        MPI_Recv(msg, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received message: %s\n", rank, msg);
    }

    MPI_Finalize();
    return 0;
}




/*
output :- 
mpicc p5_short.c -o p5_short
mpirun -np 4 ./p5_short   --> here 6 means 0,1,2,3,4,5

//if 2nd output command doesnt work then try  these :- 
mpirun --oversubscribe --mca btl self,vader -np 6 ./p5_short
mpirun --oversubscribe -np 6 ./p5_short


Process 0 sent message to process 1
Process 0 sent message to process 2
Process 0 sent message to process 3
Process 0 sent message to process 4
Process 0 sent message to process 5
Process 1 received message: Hello from process 0 to process 1
Process 2 received message: Hello from process 0 to process 2
Process 5 received message: Hello from process 0 to process 5
Process 3 received message: Hello from process 0 to process 3
Process 4 received message: Hello from process 0 to process 4


*/
