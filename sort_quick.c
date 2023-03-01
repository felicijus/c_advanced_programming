/*
Author: Felix Schneider
Date: February 28th, 2023
Purpose: General function
*/

/*HEADER FILES INCLUDED*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

/*FUNCTION PROTOYPES DECLARED*/

/*none*/

/*CONSTANTS DEFINED*/

#define ARRAY_SIZE 800000
#define RANDOM 50

int number[ARRAY_SIZE];

/*FUNCTION*/

void random_number(int *number) {
    int i;

    for (i = 0; i < ARRAY_SIZE - 1; i++) {
        number[i] = rand() % (RANDOM);
    }
}

void random_number_omp(int *number) {
    int i;

    #pragma omp for nowait
    for (i = 0; i < ARRAY_SIZE - 1; i++) {
        number[i] = rand() % (500);
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int number[], int low, int high) {
    int pivot = number[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (number[j] <= pivot) {
            i++;
            swap(&number[i], &number[j]);
        }
    }
    swap(&number[i + 1], &number[high]);
    return (i + 1);
}

int partition_omp(int number[], int low, int high) {
    int pivot = number[high];
    int i = (low - 1);

    //#pragma omp for
    for (int j = low; j < high; j++) {
        if (number[j] <= pivot) {
            i++;
            swap(&number[i], &number[j]);
        }
    }
    swap(&number[i + 1], &number[high]);
    return (i + 1);
}

void quick_sort(int number[], int low, int high) {
    if (low < high) {
        int partition_index = partition(number, low, high);

        quick_sort(number, low, partition_index - 1);
        quick_sort(number, partition_index + 1, high);
    }
}

void quick_sort_omp(int number[], int low, int high) {
    if (low < high) {
        int partition_index = partition_omp(number, low, high);

        #pragma omp task firstprivate(number,low,partition_index) default(none)
        quick_sort_omp(number, low, partition_index - 1);
        quick_sort_omp(number, partition_index + 1, high);
    }
}

int main(void) {

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

    printf("\nSorting numbers with OpenMP\n");
    start = omp_get_wtime();
    quick_sort_omp(number, 0, ARRAY_SIZE - 1);
    finish = omp_get_wtime();
    printf("Time: %f", (finish - start));

    printf("\n");

    system("PAUSE");
    system("cls");
    main();

    return 0;
}