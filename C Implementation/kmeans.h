#include "utilities.h"

void kmeans();
void initialize_centroids(Instance* cluster_centroids, Instance* instances);
void calculate_distances_to_clusters(double* distances_to_clusters, Instance* cluster_centroids, Instance* instance);
int find_min_distance_index(double* distances);
void assign_to_closest_centroid(double* distances, Instance* instance, Instance clusters[NUMBER_OF_CLUSTERS][NUMBER_OF_ELEMENTS],int* cluster_trackers);
void find_means_and_update_centroids(Instance clusters[NUMBER_OF_CLUSTERS][NUMBER_OF_ELEMENTS], Instance* cluster_centroids, int* cluster_trackers);