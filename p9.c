/*
Write an MPI program to demonstrate MPI_Reduce and 
MPI_Allreduce (MPI_MAX, MPI_MIN, MPI_SUM, MPI_PROD).
*/


#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int rank, size;
    int value;
    int sum_result, prod_result, max_result, min_result;
    int all_sum, all_prod, all_max, all_min;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Each process sets its value
    value = rank + 1;

    printf("Process %d has value %d\n", rank, value);

    // MPI_Reduce - result only at root
    MPI_Reduce(&value, &sum_result, 1, MPI_INT,
               MPI_SUM, 0, MPI_COMM_WORLD);

    MPI_Reduce(&value, &prod_result, 1, MPI_INT,
               MPI_PROD, 0, MPI_COMM_WORLD);

    MPI_Reduce(&value, &max_result, 1, MPI_INT,
               MPI_MAX, 0, MPI_COMM_WORLD);

    MPI_Reduce(&value, &min_result, 1, MPI_INT,
               MPI_MIN, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("\n--- Results using MPI_Reduce ---\n");
        printf("Sum = %d\n", sum_result);
        printf("Prod = %d\n", prod_result);
        printf("Max = %d\n", max_result);
        printf("Min = %d\n", min_result);
    }

    // MPI_Allreduce - result sent to all processes
    MPI_Allreduce(&value, &all_sum, 1, MPI_INT,
                  MPI_SUM, MPI_COMM_WORLD);

    MPI_Allreduce(&value, &all_prod, 1, MPI_INT,
                  MPI_PROD, MPI_COMM_WORLD);

    MPI_Allreduce(&value, &all_max, 1, MPI_INT,
                  MPI_MAX, MPI_COMM_WORLD);

    MPI_Allreduce(&value, &all_min, 1, MPI_INT,
                  MPI_MIN, MPI_COMM_WORLD);

    printf("Process %d - AllReduce: Sum=%d Prod=%d Max=%d Min=%d\n",
           rank, all_sum, all_prod, all_max, all_min);

    MPI_Finalize();

    return 0;
}


/*
output:-
mpicc p9.c -o p9
mpirun --oversubscribe -np 2 ./p9   --->  Run with 2 processes


Process 1 has value 2
Process 1 - AllReduce: Sum=3 Prod=2 Max=2 Min=1
Process 0 has value 1

--- Results using MPI_Reduce ---
Sum = 3
Prod = 2
Max = 2
Min = 1
Process 0 - AllReduce: Sum=3 Prod=2 Max=2 Min=1


*/
