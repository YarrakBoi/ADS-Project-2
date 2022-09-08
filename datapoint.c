#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "dictionary.h"
#include "datapoint.h"

struct point2d {
    long double x_coordinate;
    long double y_coordinate;
    dataDict_t* info;
};

struct dataDict {
    int footpath_id;
    char* address;
    char* clue_sa;
    char* asset_type;
    double deltaz;
    double distance;
    double grade1in;
    int mcc_id;
    int mccid_int;
    double rlmax;
    double rlmin;
    char* segside; 
    int statusid;
    int streetid;
    int street_group;
    double start_lat;
    double start_lon;
    double end_lat;
    double end_lon;
};

point_t* create_point(long double x, long double y, dataDict_t* info) {
    point_t* temp_point = (point_t*) malloc(sizeof(*temp_point));
    temp_point->x_coordinate = x;
    temp_point->y_coordinate = y;
    temp_point->info = info;
    return temp_point;
}

void print_point(point_t* data) {
    printf("%Lf %Lf\n", data->x_coordinate,data->y_coordinate);
    print_data(data->info);
}

void free_point(point_t* d) {
    free_struct(d->info);
    free(d);
}

