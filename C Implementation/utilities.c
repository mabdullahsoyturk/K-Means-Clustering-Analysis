#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include "utilities.h"

double rand_from(double min, double max) {
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

Min_Max_Pair getMinMax(double arr[], int n) { 
    Min_Max_Pair minmax;      
    int i; 
    
    /*If there is only one element then return it as min and max both*/
    if (n == 1) { 
        minmax.max = arr[0]; 
        minmax.min = arr[0];      
        return minmax; 
    }     
    
    /* If there are more than one elements, then initialize min and max*/
    if (arr[0] > arr[1]) { 
        minmax.max = arr[0]; 
        minmax.min = arr[1]; 
    } else { 
        minmax.max = arr[1]; 
        minmax.min = arr[0]; 
    }     
  
    for (i = 2; i < n; i++) { 
        if (arr[i] >  minmax.max) {
            minmax.max = arr[i];
        }        
        
        else if (arr[i] <  minmax.min) {
            minmax.min = arr[i];
        }        
    } 
    
    return minmax; 
} 

// This functions reads a feature of the instance
void get_features(char* line, double *features) {
    char *tok = strtok(line, ",");
    int count = 0;
    features[count] = atof(tok);

    while (tok != NULL) {
        count++;
        tok = strtok(NULL, ",");
        if(tok != NULL) {
            features[count] = atof(tok);
        }
    }
}

// This functions reads all instances from the csv file
void read_instances(char* file_name, Instance* instances) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(file_name, "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    int counter = 0;

    while ((read = getline(&line, &len, fp)) != -1) {
        Instance instance;
        double features[NUMBER_OF_FEATURES];
        get_features(line, features);

        for(int i = 0; i < NUMBER_OF_FEATURES; i++) {
            instances[counter].features[i] = features[i];
        }

        counter++;
    }

    fclose(fp);
    if (line) {
        free(line);
    }
}
