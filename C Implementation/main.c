#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include "kmeans.h"

void kmeans(Instance* instances, Instance* cluster_centroids) {
    int counter = 0;

    while(counter < MAX_ITERATIONS) {
        Instance clusters[3][NUMBER_OF_ELEMENTS];
        double distances_to_clusters[3];
        int cluster_trackers[3];

        for(int i = 0; i < NUMBER_OF_CLUSTERS; i++) {
            cluster_trackers[i] = 0;
        }

        for(int i = 0; i < NUMBER_OF_ELEMENTS; i++) {
            // Find the eucledian distance between all points to the centroids
            calculate_distances_to_clusters(distances_to_clusters, cluster_centroids, &instances[i]);

            // Find the closest centroid to the point and assign the point to that cluster
            assign_to_closest_centroid(distances_to_clusters, &instances[i], clusters, cluster_trackers);
        }

        Instance previous_centroids[3];  // Store previous centroids to compare
        for(int i = 0; i < NUMBER_OF_CLUSTERS; i++) {
            previous_centroids[i].sepal_length = cluster_centroids[i].sepal_length;
            previous_centroids[i].sepal_width = cluster_centroids[i].sepal_width;
            previous_centroids[i].petal_length = cluster_centroids[i].petal_length;
            previous_centroids[i].petal_width = cluster_centroids[i].petal_width;
        }

        for(int i = 0; i < NUMBER_OF_CLUSTERS; i++) {
            printf("%d ", cluster_trackers[i]);
        }

         // Find mean of all points within a cluster and make it as the centroid 
        find_means_and_update_centroids(clusters, cluster_centroids, cluster_trackers);

        // If centroid values hasn't changed, algorithm has convereged 
        if(cluster_centroids[0].sepal_length == previous_centroids[0].sepal_length &&
           cluster_centroids[1].sepal_length == previous_centroids[1].sepal_length && 
           cluster_centroids[2].sepal_length == previous_centroids[2].sepal_length &&
           cluster_centroids[0].sepal_width == previous_centroids[0].sepal_width &&
           cluster_centroids[1].sepal_width == previous_centroids[1].sepal_width &&
           cluster_centroids[2].sepal_width == previous_centroids[2].sepal_width &&
           cluster_centroids[0].petal_length == previous_centroids[0].petal_length &&
           cluster_centroids[1].petal_length == previous_centroids[1].petal_length &&
           cluster_centroids[2].petal_length == previous_centroids[2].petal_length &&
           cluster_centroids[0].petal_width == previous_centroids[0].petal_width &&
           cluster_centroids[1].petal_width == previous_centroids[1].petal_width &&
           cluster_centroids[2].petal_width == previous_centroids[2].petal_width ) {
                printf("Converged\n");
                break;
        }

        counter++;
    }
}

int main(int argc, char const *argv[]) {
    Instance instances[NUMBER_OF_ELEMENTS]; 
    Instance cluster_centroids[NUMBER_OF_CLUSTERS];

    initialize_centroids(cluster_centroids);
    read_instances("iris.csv", instances);

    kmeans(instances, cluster_centroids);
    for(int i = 0; i < NUMBER_OF_ELEMENTS; i++) {
        printf("Cluster%d: %f\n",i, instances[i].cluster);
    }
}