/*
Write an MPI program to demonstrate MPI_Scatter and MPI_Gather.
*/

#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size, data[100], recv, gathered[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank==0) {
        for(int i=0;i<size;i++) data[i]=i*10;
        printf("Process 0 initialized data: ");
        for(int i=0;i<size;i++) printf("%d ",data[i]);
        printf("\n");
    }

    MPI_Scatter(data,1,MPI_INT,&recv,1,MPI_INT,0,MPI_COMM_WORLD);
    printf("Process %d received value %d from Scatter\n",rank,recv);

    recv+=rank;
    MPI_Gather(&recv,1,MPI_INT,gathered,1,MPI_INT,0,MPI_COMM_WORLD);

    if(rank==0) {
        printf("Process 0 gathered data: ");
        for(int i=0;i<size;i++) printf("%d ",gathered[i]);
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}


/*
mpicc p8_short.c -o p8_short
mpirun --oversubscribe -np 4 ./p8_short


Process 1 received value 10 from Scatter
Process 2 received value 20 from Scatter
Process 0 initialized data: 0 10 20 30 
Process 0 received value 0 from Scatter
Process 3 received value 30 from Scatter
Process 0 gathered data: 0 11 22 33 

*/
