/*
Question:
Write an OpenMP program to find the prime numbers from 1 to n
employing parallel for directive. Record both serial and parallel
execution times.
*/




#include <stdio.h>
#include <math.h>
#include <omp.h>

int is_prime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

int main() {
    int n, serial=0, parallel=0;
    printf("Enter value of n: ");
    scanf("%d",&n);

    double s=omp_get_wtime();
    for(int i=1;i<=n;i++) serial+=is_prime(i);
    double t=omp_get_wtime()-s;

    s=omp_get_wtime();
    #pragma omp parallel for reduction(+:parallel)
    for(int i=1;i<=n;i++) parallel+=is_prime(i);
    s=omp_get_wtime()-s;

    printf("\nSerial Execution Time: %f seconds\n",t);
    printf("Parallel Execution Time: %f seconds\n",s);
    printf("Primes found (Serial): %d, (Parallel): %d\n",serial,parallel);

    return 0;
}








/*
outut:-

gcc -fopenmp p4_short.c -o p4_short -lm
./p4_short

Enter value of n: 10000000

Serial Execution Time: 2.468344 seconds
Parallel Execution Time: 0.836786 seconds
Primes found (Serial): 664579, (Parallel): 664579


*/
