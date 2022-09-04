#include <stdbool.h>
#include <math.h>
#include "quadtree.h"
#include "dictionary.h"

//0 for SW,1 for SE, 2 for NE, 3 for NW
enum quadrants{0,1,2,3};

struct point2d {
    long double x_coordinate;
    long double y_coordinate;
}

struct rectangle {
    long double bot_left_x;
    long double bot_left_y;
    long double top_right_x;
    long double top_right_y;
};

struct node {
    boolean is_internal_root = false;
    rectangle_t* bounding_box;
    point_t* point;
    node_t* NW = NULL;
    node_t* NE = NULL;
    node_t* SW = NULL;
    node_t* SE = NULL;
}

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

int determine_quadrants(rectangle_t* bounding_box, point_t* point) {
    long double rectangle_length = fabs(bounding_box->bot_left_x - bounding_box->top_right_x);
    long double rectangle_height = fabs(bounding_box->bot_left_y - bounding_box->top_right_y);
}

node_t* create_node(long double latitude_y,long double longitude_x,long double bot_left_x,long double bot_left_y,long double top_right_x,long double top_right_y) {
    node_t* temp = (node_t*) malloc(sizeof(*temp));
    assert(temp);
    temp->create_rectangle(bot_left_x,bot_left_y,top_right_x,top_right_y);
    temp->create_point(longitude_x,latitude_y);
    return temp;
}

point_t* create_point(long double x_coordinate_copied, long double y_coordinate_copied) {
    point_t* temp = (point_t*) malloc(sizeof(*temp));
    assert(temp);
    temp->x_coordinate = strtod(x_coordinate_copied,NULL);
    temp->y_coordinate = strtod(y_coordinate_copied,NULL);
    return temp;
}

rectangle_t* create_rectangle(long double bot_left_x,long double bot_left_y,long double top_right_x,long double top_right_y) {
    rectangle_t* temp = (rectangle_t*) malloc(sizeof(*temp));
    assert(temp);
    temp->bot_left_x = strtod(bot_left_x,NULL);
    temp->bot_left_y = strtod(bot_left_y,NULL);
    temp->top_right_x = strtod(top_right_x,NULL);
    temp->top_right_y = strtod(top_right_y,NULL);
    return temp;
}



void free_node(node_t * root) {

}