//
// Created by Felix on 21.03.2023.
//

#include <stdio.h>
#include <stdint.h>
#include <omp.h>

uint64_t UPPER = 10000;

uint64_t perfect_number(uint64_t number){
    uint64_t sum = 0;

#pragma omp for nowait
    for(uint64_t i = 1; i < number; i++){
        if (number % i == 0)
            sum += i;
    }

    if(sum == number){
        return sum;
    }
    return 0;
}

int main(void){

#pragma omp for nowait
    for(uint64_t i = 1; i < UPPER; i++){
        uint64_t p = perfect_number(i);
        if(p != 0){
            printf("%I64d\n",p);
        }
    }
}
