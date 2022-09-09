#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include "dictionary.h"
#include "quadtree.h"
#include "datapoint.h"
#include "list.h"

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

struct quadtree {
    bool is_internal_root;
    rectangle_t* bounding_box;
    point_t* point;
    node_t* info_list;
    quadtree_t* NW;
    quadtree_t* NE;
    quadtree_t* SW;
    quadtree_t* SE;
};

struct Node {
    dataDict_t* data;
    node_t *next;
};

int main(int argc, char **argv) {
    dataDict_t* temp;
    point_t* point_temp;
    point_t* point_temp2;
    quadtree_t* quad_root;
    FILE *in_fp = fopen(argv[2],"r");
    FILE *out_fp = fopen(argv[3],"w");
    char row[MAXCHAR];
    long double x_temp;
    long double y_temp;
    char* query_point;

    assert(in_fp && out_fp);
    
    // remove header
    fgets(row, MAXCHAR, in_fp);
    
    quad_root = create_tree(create_rectangle(strtold(argv[4],NULL),strtold(argv[5],NULL),strtold(argv[6],NULL),strtold(argv[7],NULL)));

    //read in data, create point and insert to quadtree
    while (((temp) = data_dict_read(in_fp)) != NULL) {
        point_temp = create_point(temp->start_lon, temp->start_lat);
        quad_root = insert_node(point_temp,quad_root,temp);
        point_temp2 = create_point(temp->end_lon, temp->end_lat);
        quad_root = insert_node(point_temp2,quad_root,temp);
    }
    assert(quad_root != NULL);
    
    //closing after reading required input
    fclose(in_fp);

    while (fscanf(stdin,"%s\n",query_point) == 2) {
        point_temp = create_point(strtold(x_string,NULL),strtold(y_string,NULL));
        printf("%s %s -->",x_string,y_string);
        search_quadtree(point_temp,quad_root,out_fp);
        free_point(point_temp);
    }
    return 0;
}
