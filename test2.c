#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include "dictionary.h"
#include "quadtree.h"
#include "datapoint.h"

//512 char + null byte
#define MAXCHAR 513

//128 char with null byte
#define MAX_FIELD_CHAR 129

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

struct point2d {
    long double x_coordinate;
    long double y_coordinate;
    dataDict_t* info;
};

int main(int argc, char **argv) {
    dataDict_t* temp;
    point_t* point_temp;
    point_t* point_temp2;
    quadtree_t* quad_root;
    FILE *in_fp = fopen("tests/dataset_20.csv","r");
    char row[MAXCHAR];

    //assert(in_fp && out_fp);
    assert(in_fp);
    // remove header
    fgets(row, MAXCHAR, in_fp);
    
    quad_root = create_tree(create_rectangle(144.952,-37.81,144.978,-37.79));
    //read in data, craete point and insert to quadtree
    while (((temp) = data_dict_read(in_fp)) != NULL) {
        point_temp = create_point(temp->start_lon, temp->start_lat, temp);
        quad_root = insert_node(point_temp,quad_root);
        point_temp2 = create_point(temp->end_lon, temp->end_lat, temp);
        quad_root = insert_node(point_temp2,quad_root);
        printf("entry completed\n");
        printf("breakpointhere");
    }
    assert(quad_root != NULL);
    
    //closing after reading required input
    fclose(in_fp);

    return 0;
}
