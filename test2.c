#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include "dictionary.h"
#include "list.h"
#include "datapoint.h"
#include "datalist.h"

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

struct Node {
    dataDict_t* data;
    node_t *next;
};

struct point2d {
    long double x_coordinate;
    long double y_coordinate;
};

struct data_point {
    point_t* start_coordinate_point;
    point_t* end_coordinate_point;
    dataDict_t* info;
};

int main(int argc, char **argv) {
    
    dataDict_t* temp;
    data_point_t* data_point_temp;
    FILE *in_fp = fopen("tests/dataset_1.csv","r");
    char row[MAXCHAR];
    char line[MAX_FIELD_CHAR];
    data_node_t *head = NULL;
    int address_count = 0;

    //assert(in_fp && out_fp);
    assert(in_fp);
    // remove header
    fgets(row, MAXCHAR, in_fp);
    
    //create structs and populate linked list
    while (((temp) = data_dict_read(in_fp)) != NULL) {
        data_point_temp = create_data_point(temp);
        head = create_datalist(head,data_point_temp);
    }
    assert(head != NULL);
    
    //closing after reading required input
    fclose(in_fp);

    print_datalist(head);


    return 0;
}
