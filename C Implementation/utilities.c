#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include "utilities.h"

double rand_from(double min, double max) {
    // srand ( time(NULL) );
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
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
        double features[4];
        get_features(line, features);
        instances[counter].petal_length = features[0];
        instances[counter].petal_width = features[1];
        instances[counter].sepal_length = features[2];
        instances[counter].sepal_width = features[3];

        counter++;
    }

    fclose(fp);
    if (line) {
        free(line);
    }
}
