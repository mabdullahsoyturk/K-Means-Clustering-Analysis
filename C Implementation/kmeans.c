#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include "kmeans.h"
#include <stdbool.h>

#define DATASET_NAME "iris.csv"

void kmeans() {
    int counter = 0;
    Instance* instances = malloc(sizeof(Instance) * NUMBER_OF_ELEMENTS);
    Instance* cluster_centroids = malloc(sizeof(Instance) * NUMBER_OF_CLUSTERS);

    read_instances(DATASET_NAME, instances);
    initialize_centroids(cluster_centroids, instances);

    for(int i = 0; i < NUMBER_OF_CLUSTERS; i++) {
        printf("Cluster%d center at the beginning: ", i);
        for(int k = 0; k < NUMBER_OF_FEATURES; k++) {
            printf("%f ", cluster_centroids[i].features[k]);
        }
        printf("\n");
    }

    while(counter < MAX_ITERATIONS) {
        Instance clusters[NUMBER_OF_CLUSTERS][NUMBER_OF_ELEMENTS];
        double* distances_to_clusters = malloc(sizeof(double) * NUMBER_OF_CLUSTERS);
        int* cluster_trackers = malloc(sizeof(int) * NUMBER_OF_CLUSTERS);

        for(int i = 0; i < NUMBER_OF_CLUSTERS; i++) {
            cluster_trackers[i] = 0;
        }

        for(int i = 0; i < NUMBER_OF_ELEMENTS; i++) {
            // Find the eucledian distance between all points to the centroids
            calculate_distances_to_clusters(distances_to_clusters, cluster_centroids, &instances[i]);

            // Find the closest centroid to the point and assign the point to that cluster
            assign_to_closest_centroid(distances_to_clusters, &instances[i], clusters, cluster_trackers);
        }
        free(distances_to_clusters);

        Instance* previous_centroids = malloc(sizeof(Instance) * NUMBER_OF_CLUSTERS); 
        for(int i = 0; i < NUMBER_OF_CLUSTERS; i++) {
            for(int k = 0; k < NUMBER_OF_FEATURES; k++) { // Store previous centroids to compare
                previous_centroids[i].features[k] = cluster_centroids[i].features[k];
            }
        }

        printf("Cluster info after iteration %d\n", counter);
        for(int i = 0; i < NUMBER_OF_CLUSTERS; i++) {
            printf("%d\t", cluster_trackers[i]);
        }
        printf("\n");

         // Find mean of all points within a cluster and make it as the centroid 
        find_means_and_update_centroids(clusters, cluster_centroids, cluster_trackers);
        free(cluster_trackers);

        // If centroid values hasn't changed, algorithm has convereged
        bool stop = true;

        for(int i = 0; i < NUMBER_OF_CLUSTERS; i++) {
            for(int k = 0; k < NUMBER_OF_FEATURES; k++) {
                if(cluster_centroids[i].features[k] != previous_centroids[i].features[k]) {
                    stop = false;
                }
            }
        }

        free(previous_centroids);

        if(stop) {
            printf("\nConverged\n\n");
            break;
        }

        counter++;
    }

    for(int i = 0; i < NUMBER_OF_CLUSTERS; i++) {
        printf("Cluster%d center at the end: ", i);
        for(int k = 0; k < NUMBER_OF_FEATURES; k++) {
            printf("%f ", cluster_centroids[i].features[k]);
        }
        printf("\n");
    }

    free(cluster_centroids);
    free(instances);
}

void initialize_centroids(Instance* cluster_centroids, Instance* instances) {
    srand (time(NULL));
    Min_Max_Pair* mins_and_maxes = malloc(sizeof(Min_Max_Pair) * NUMBER_OF_FEATURES);
    get_mins_and_maxes(instances, mins_and_maxes);

    for(int i = 0; i < NUMBER_OF_CLUSTERS; i++) {
        for(int k = 0; k < NUMBER_OF_FEATURES; k++) {
            cluster_centroids[i].features[k] = rand_from(mins_and_maxes[k].min,mins_and_maxes[k].max);            
        }
    }
    free(mins_and_maxes);
}

void calculate_distances_to_clusters(double* distances_to_clusters, Instance* cluster_centroids, Instance* instance) {
    for(int i = 0; i < NUMBER_OF_CLUSTERS; i++) {
        double sum = 0;

        for(int k = 0; k < NUMBER_OF_FEATURES; k++) {
            sum += sqr(cluster_centroids[i].features[k] - instance->features[k]);
        }

        distances_to_clusters[i] = sqrt(sum);
    }
}

int find_min_distance_index(double* distances) {
    int min = INF;
    int index = -1;

    for(int i = 0; i < NUMBER_OF_CLUSTERS; i++) {
        if(distances[i] < min) {
            min = distances[i];
            index = i;
        }
    }

    return index;
}

void assign_to_closest_centroid(double* distances, Instance* instance, Instance clusters[NUMBER_OF_CLUSTERS][NUMBER_OF_ELEMENTS], int* cluster_trackers) {
    int min_distance_index = find_min_distance_index(distances);

    for(int i = 0; i < NUMBER_OF_CLUSTERS; i++) {
        if(min_distance_index == i) {
            instance->cluster = i;
            clusters[i][cluster_trackers[i]] = *instance;
            cluster_trackers[i]++;
        }
    }
}

void find_means_and_update_centroids(Instance clusters[NUMBER_OF_CLUSTERS][NUMBER_OF_ELEMENTS], Instance* cluster_centroids, int* cluster_trackers) {     
    for(int i = 0; i < NUMBER_OF_CLUSTERS; i++) {
        double* cluster_totals = malloc(sizeof(double) * NUMBER_OF_FEATURES);
        for(int k = 0; k < NUMBER_OF_FEATURES; k++) {
            cluster_totals[k] = 0;
        }

        for(int k = 0; k < cluster_trackers[i]; k++) {
            for(int j = 0; j < NUMBER_OF_FEATURES; j++) {
                cluster_totals[j] += clusters[i][k].features[j];
            }
        }

        if(cluster_trackers[i] != 0) {
            for(int k = 0; k < NUMBER_OF_FEATURES; k++) {
                cluster_centroids[i].features[k] = cluster_totals[k] / (double)cluster_trackers[i];
            }
        }
        free(cluster_totals);
    }
}