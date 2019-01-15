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

int main(int argc, char const *argv[]) {
    clock_t begin = clock();

    kmeans();

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("\nTime consumed: %f\n", time_spent);
}