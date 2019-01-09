#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include "kmeans.h"

void initialize_centroids(Instance* cluster_centroids) {
    srand (time(NULL));
    for(int i = 0; i < NUMBER_OF_CLUSTERS; i++) {
        cluster_centroids[i].features[0] = rand_from(4,8);
        cluster_centroids[i].features[1] = rand_from(1,5);
        cluster_centroids[i].features[2] = rand_from(1,7);
        cluster_centroids[i].features[3] = rand_from(0.1,3);
    }
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

void assign_to_closest_centroid(double* distances, Instance* instance, Instance clusters[3][NUMBER_OF_ELEMENTS], int* cluster_trackers) {
    int min_distance_index = find_min_distance_index(distances);

    if(min_distance_index == 0) {
        instance->cluster = 0;
        clusters[0][cluster_trackers[0]] = *instance;
        cluster_trackers[0]++;
    }else if (min_distance_index == 1) {
        instance->cluster = 1;
        clusters[1][cluster_trackers[1]] = *instance;
        cluster_trackers[1]++;
    }else if(min_distance_index == 2) {
        instance->cluster = 2;
        clusters[2][cluster_trackers[2]] = *instance;
        cluster_trackers[2]++;
    }
}

void find_means_and_update_centroids(Instance clusters[3][NUMBER_OF_ELEMENTS], Instance* cluster_centroids, int* cluster_trackers) {
    for(int i = 0; i < NUMBER_OF_CLUSTERS; i++) {
        double cluster_totals[NUMBER_OF_FEATURES];

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
    }
}