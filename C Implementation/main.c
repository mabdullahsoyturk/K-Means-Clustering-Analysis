#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "kmeans.h"

int main(int argc, char const *argv[]) {
    clock_t begin = clock();

    kmeans();

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("\nTime consumed: %f\n", time_spent);
}