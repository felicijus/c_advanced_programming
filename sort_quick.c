
/*
Author: Felix Schneider
Date: February 28th, 2023
Purpose: General function
*/

/*HEADER FILES INCLUDED*/

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/*FUNCTION PROTOTYPES DECLARED*/

/*none*/

/*CONSTANTS DEFINED*/

#define ARRAY_SIZE 10000000
#define RANDOM 10000


/*FUNCTION*/

void random_number(int *array) {
    for (int i = 0; i <= ARRAY_SIZE - 1; i++) {
        array[i] = rand() % RANDOM + 1;
    }
}

void random_number_omp(int *array) {
    #pragma omp for nowait
    for (int i = 0; i <= ARRAY_SIZE - 1; i++) {
        array[i] = rand() % RANDOM + 1;
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *array, int low, int high) {
    int pivot = array[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1 ; j++) {
        if (array[j] < pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
void quick_sort(int *array, int low, int high) {
    if (low < high) {
        int partition_index = partition(array, low, high);

        quick_sort(array, low, partition_index - 1);
        quick_sort(array, partition_index + 1, high);
    }
}

#pragma clang diagnostic pop
void quick_sort_omp(int array[], int low, int high) {
    if (low < high) {
        int partition_index = partition(array, low, high);

        #pragma omp task shared(array, low, partition_index) default(none)
        quick_sort_omp(array, low, partition_index - 1);

        #pragma omp task shared(array, high, partition_index) default(none)
        quick_sort_omp(array, partition_index + 1, high);
    }
}

int main(void) {

    // int number[ARRAY_SIZE];

    int *number = calloc(ARRAY_SIZE, sizeof(int));

    // Time
    double start, finish;

    printf("This is the QuickSort algorithm.\n");

    //Single
    printf("\nRandom numbers\n");
    start = omp_get_wtime();
    random_number(number);
    finish = omp_get_wtime();
    printf("Time: %f", (finish - start));

    printf("\nSorting numbers\n");
    start = omp_get_wtime();
    quick_sort(number, 0, ARRAY_SIZE - 1);
    finish = omp_get_wtime();
    printf("Time: %f", (finish - start));

    printf("\n");

    //OpenMP
    printf("\nRandom numbers with OpenMP\n");
    start = omp_get_wtime();
    random_number_omp(number);
    finish = omp_get_wtime();
    printf("Time: %f", (finish - start));

    printf("\nSorting numbers with OpenMP and %i processing cores\n", omp_get_num_procs());
    start = omp_get_wtime();

    #pragma omp parallel shared(number) default(none)
    {
        #pragma omp single
        quick_sort_omp(number, 0, ARRAY_SIZE - 1);
        #pragma omp taskwait
    }

    finish = omp_get_wtime();
    printf("Time: %f", (finish - start));

    return 0;
}
#pragma clang diagnostic pop