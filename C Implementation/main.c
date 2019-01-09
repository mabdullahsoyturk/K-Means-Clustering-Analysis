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

void kmeans(Instance* instances, Instance* cluster_centroids) {
    int counter = 0;

    while(counter < MAX_ITERATIONS) {
        Instance clusters[NUMBER_OF_CLUSTERS][NUMBER_OF_ELEMENTS];
        double distances_to_clusters[NUMBER_OF_CLUSTERS];
        int cluster_trackers[NUMBER_OF_CLUSTERS];

        for(int i = 0; i < NUMBER_OF_CLUSTERS; i++) {
            cluster_trackers[i] = 0;
        }

        for(int i = 0; i < NUMBER_OF_ELEMENTS; i++) {
            // Find the eucledian distance between all points to the centroids
            calculate_distances_to_clusters(distances_to_clusters, cluster_centroids, &instances[i]);

            // Find the closest centroid to the point and assign the point to that cluster
            assign_to_closest_centroid(distances_to_clusters, &instances[i], clusters, cluster_trackers);
        }

        Instance previous_centroids[NUMBER_OF_CLUSTERS];  // Store previous centroids to compare
        for(int i = 0; i < NUMBER_OF_CLUSTERS; i++) {
            for(int k = 0; k < NUMBER_OF_FEATURES; k++) {
                previous_centroids[i].features[k] = cluster_centroids[i].features[k];
            }
        }

        for(int i = 0; i < NUMBER_OF_CLUSTERS; i++) {
            printf("%d ", cluster_trackers[i]);
        }

         // Find mean of all points within a cluster and make it as the centroid 
        find_means_and_update_centroids(clusters, cluster_centroids, cluster_trackers);

        // If centroid values hasn't changed, algorithm has convereged
        bool stop = true;

        for(int i = 0; i < NUMBER_OF_CLUSTERS; i++) {
            for(int k = 0; k < NUMBER_OF_FEATURES; k++) {
                if(cluster_centroids[i].features[k] != previous_centroids[i].features[k]) {
                    stop = false;
                }
            }
        }

        if(stop) {
            printf("Converged\n");
            break;
        }

        counter++;
    }
}

int main(int argc, char const *argv[]) {
    Instance instances[NUMBER_OF_ELEMENTS]; 
    Instance cluster_centroids[NUMBER_OF_CLUSTERS];

    read_instances(DATASET_NAME, instances);
    
    clock_t begin = clock();
    initialize_centroids(cluster_centroids);

    kmeans(instances, cluster_centroids);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Time consumed: %f\n", time_spent);
    // for(int i = 0; i < NUMBER_OF_ELEMENTS; i++) {
    //     printf("Cluster of instance %d : %d\n", i, (int)instances[i].cluster);
    // }
}