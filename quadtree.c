#include "quadtree.h"
#include "dictionary.h"

struct rectangle {
    long double bot_left_x;
    long double bot_left_y;
    long double top_right_x;
    long double top_right_y;
};

struct node {
    rectangle_t* bounding_box;


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

rectangle_t* create_rectangle(long double bot_left_x,long double bot_left_y,long double top_right_x,long double top_right_y) {
    rectangle_t* temp = NULL;
    temp->bot_left_x = strtod(bot_left_x,NULL);
    temp->bot_left_y = strtod(bot_left_y,NULL);
    temp->top_right_x = strtod(top_right_x,NULL);
    temp->top_right_y = strtod(top_right_y,NULL);
    return temp;
}

void free_node(node_t * root) {

}