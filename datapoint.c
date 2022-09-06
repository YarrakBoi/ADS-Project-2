#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "datapoint.h"
#include "list.h"

struct point2d {
    long double x_coordinate;
    long double y_coordinate;
};

struct data_point {
    point_t* start_coordinate_point;
    point_t* end_coordinate_point;
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

struct Node {
    dataDict_t* data;
    node_t *next;
};

point_t* create_point(long double x,long double y) {
    point_t* temp_point = (point_t*) malloc(sizeof(*temp_point));
    
    temp_point->x_coordinate = x;
    temp_point->y_coordinate = y;
    return temp_point;
}

data_point_t* create_data_point(node_t* node_info) {
    data_point_t* data_temp = (data_point_t*) malloc(sizeof(*data_temp));
    assert(data_temp);
    data_temp->info = node_info->data;
    data_temp->start_coordinate_point = create_point(node_info->data->start_lon,node_info->data->start_lat);
    data_temp->end_coordinate_point = create_point(node_info->data->end_lon,node_info->data->end_lat);
    return data_temp;
}
