#define NUMBER_OF_ELEMENTS 150
#define NUMBER_OF_FEATURES 4
#define NUMBER_OF_CLUSTERS 3
#define MAX_ITERATIONS 100
#define sqr(x) ((x) * (x))
#define INF 999999999

typedef struct Instance { 
    double sepal_length;
    double sepal_width;
    double petal_length;
    double petal_width;
    double cluster;
}Instance;

void get_features(char* line, double *features);
void read_instances(char* file_name, Instance* instances);
double rand_from(double min, double max);