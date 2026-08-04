/*
Write an OpenMP program to calculate n Fibonacci numbers using tasks.
*/

#include<stdio.h>
#include<omp.h>

int fib_task(int n) {
  int x,y;
  if(n<2)  return n;
  
  #pragma omp task shared(x)
  x = fib_task(n-1);
  #pragma omp task shared(y)
  y = fib_task(n-2);
  #pragma omp taskwait
  return x+y;
}

int main() {
  int n;
  printf("Enter the number of Fibonacci terms: ");
  scanf("%d", &n);
  printf("Fibonacci series: \n");
  
  #pragma omp parallel
  {
    #pragma omp single
    {
      for(int i=0 ; i<n; i++) {
        int result = fib_task(i);
        printf("fib(%d) = %d\n", i , result);
      }
    }
  }
  
  return 0;
}
