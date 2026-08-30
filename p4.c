/*
Question:
Write an OpenMP program to find the prime numbers from 1 to n
employing parallel for directive. Record both serial and parallel
execution times.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

int is_prime(int num) {
    if (num < 2) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;

    int limit = sqrt(num);

    for (int i = 3; i <= limit; i += 2) {
        if (num % i == 0) return 0;
    }

    return 1;
}

int main() {
    int n;

    printf("Enter value of n: ");
    scanf("%d", &n);

    double start_time, end_time;

    // Serial Execution
    start_time = omp_get_wtime();

    int serial_count = 0;

    for (int i = 2; i <= n; i++) {
        if (is_prime(i))
            serial_count++;
    }

    end_time = omp_get_wtime();

    printf("Serial Execution Time: %f seconds\n",
           end_time - start_time);

    // Parallel Execution
    omp_set_num_threads(4); // Set based on CPU

    int *prime_flags = (int *)calloc(n + 1, sizeof(int));

    start_time = omp_get_wtime();

    #pragma omp parallel for schedule(dynamic, 100)
    for (int i = 2; i <= n; i++) {
        if (is_prime(i)) {
            prime_flags[i] = 1;
        }
    }

    end_time = omp_get_wtime();

    int parallel_count = 0;

    for (int i = 2; i <= n; i++) {
        if (prime_flags[i])
            parallel_count++;
    }

    printf("Parallel Execution Time: %f seconds\n",
           end_time - start_time);

    printf("Primes found (Serial): %d, (Parallel): %d\n",
           serial_count, parallel_count);

    free(prime_flags);

    return 0;
}

/*
outut:-

gcc -fopenmp p4.c -o p4 -lm
./p4

Enter value of n: 10000000

Serial Execution Time: 1.968814 seconds
Parallel Execution Time: 0.682501 seconds
Primes found (Serial): 664579, (Parallel): 664579

*/
