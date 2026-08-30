/*Write an OpenMP program to sort an array of n elements using both sequential and parallel Merge Sort (using OpenMP Sections/Tasks). Record  the difference in execution. */


#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>
#include<math.h>
#define THRESHOLD 10000

void merge_with_buffer(int arr[],int left,int mid,int right, int* buffer) {
  int i,j,k;
  int n1=mid-left+1;
  int n2=right-mid;
  for(i=0;i<n1;i++)   buffer[i] = arr[left+i];
  for(j=0;j<n2;j++)   buffer[n1+j] = arr[mid+1+j];
  i=0;
  j=n1;
  k=left;
  
  while(i<n1 && j<n1+n2) {
    if(buffer[i] <= buffer[j]) {
      arr[k++] = buffer[i++];
    } else {
      arr[k++] = buffer[j++];
    }
  }
  while(i<n1)
    arr[k++] = buffer[i++];
  while(j < n1+n2)
    arr[k++] = buffer[j++];
}

void sequential_mergesort(int arr[], int left, int right, int* buffer) {
  if(left < right) {
    int mid = left+(right-left) / 2;
    sequential_mergesort(arr,left,mid,buffer);
    sequential_mergesort(arr,mid+1,right,buffer);
    merge_with_buffer(arr,left,mid,right,buffer);
  }
}

void parallel_mergesort_improved(int arr[], int left, int right, int *buffer) {
    if (right - left < THRESHOLD) {
        sequential_mergesort(arr, left, right, buffer);
        return;
    }
    if (left < right) {
        int mid = left + (right - left) / 2;
        #pragma omp task
        parallel_mergesort_improved(arr, left, mid, buffer);
        #pragma omp task
        parallel_mergesort_improved(arr, mid + 1, right, buffer);
        #pragma omp taskwait
        merge_with_buffer(arr, left, mid, right, buffer);
    }
}

int main() {
  int n=10000000; // 1crore or 10million
  int *arr = (int *) malloc(n * sizeof(int));
  int *arr_copy = (int *)malloc(n*sizeof(int));
  int *buffer = (int *) malloc(n * sizeof(int));
  
  srand(time(NULL));
  for(int i=0;i<n;i++) {
  arr[i] = rand() % 1000000;
  arr_copy[i] = arr[i];
  }
  omp_set_nested(1);
  omp_set_num_threads(omp_get_num_procs());
  double start_time = omp_get_wtime();
  sequential_mergesort(arr,0,n-1,buffer);
  double sequential_time = omp_get_wtime() - start_time;
  start_time = omp_get_wtime();
  #pragma omp parallel
    {
        #pragma omp single
        parallel_mergesort_improved(arr_copy, 0, n - 1, buffer);
    }
    double parallel_time = omp_get_wtime() - start_time;
    printf("Sequential Time: %.6f seconds\n", sequential_time);
    printf("Parallel Time: %.6f seconds\n", parallel_time);
    printf("Time Difference: %.6f seconds\n",fabs(sequential_time -parallel_time));
    free(arr);
    free(arr_copy);
    free(buffer);
    return 0;
}

/*
output:-

gcc -fopenmp p1.c -o p1
./p1

Sequential Time: 3.478580 seconds
Parallel Time: 1.161901 seconds
Time Difference: 2.316679 seconds

*/
