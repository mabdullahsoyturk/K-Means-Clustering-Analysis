#define NUMBER_OF_ELEMENTS 150
#define NUMBER_OF_FEATURES 4
#define NUMBER_OF_CLUSTERS 3
#define MAX_ITERATIONS 100
#define DATASET_NAME "../iris.csv"

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>

typedef struct Instance { 
    double features[NUMBER_OF_FEATURES];
    double cluster;
}Instance;

typedef struct Min_Max_Pair  
{ 
  double min; 
  double max; 
} Min_Max_Pair;   

void get_features(char* line, double *features);
void read_instances(char* file_name, Instance* instances);
double rand_from(double min, double max);
Min_Max_Pair get_min_max(double* arr, int n);
void get_mins_and_maxes(Instance* instances, Min_Max_Pair* mins_and_maxes);