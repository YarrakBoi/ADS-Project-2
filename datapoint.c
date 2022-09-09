#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "datapoint.h"

struct point2d {
    long double x_coordinate;
    long double y_coordinate;
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

point_t* create_point(long double x, long double y) {
    point_t* temp_point = (point_t*) malloc(sizeof(*temp_point));
    temp_point->x_coordinate = x;
    temp_point->y_coordinate = y;
    return temp_point;
}

void print_point(point_t* data) {
    printf("%Lf %Lf\n", data->x_coordinate,data->y_coordinate);
}

void free_point(point_t* d) {
    free(d);
}

