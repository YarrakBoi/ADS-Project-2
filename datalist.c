#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "datalist.h"
#include "dictionary.h"
#include "datapoint.h"


struct data_node {
    data_point_t* data;
    data_node_t* next;
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

data_node_t* create_datanode(data_point_t* data) {
    data_node_t *temp = (data_node_t*) malloc(sizeof(*temp));
    data_node_t *empty_node = NULL;
    assert(temp);
    temp->data->info = data;
    temp->next = empty_node;
    return temp;
}

data_node_t *create_datalist(data_node_t *head, data_point_t* data) {
    data_node_t *iterator = NULL;
    data_node_t *temp = NULL;

    if(head == NULL){
        temp = create_datanode(data);
        head = temp;
    }
    else {
        temp = create_datanode(data);
        iterator = head;
        while (iterator->next != NULL) {
            iterator = iterator->next;
        }
        iterator->next = temp;
    }
    return head;
}

void print_datalist(data_node_t* head) {
    print_data(head->data);
    while (head->next != NULL) {
        print_datalist(head);
        head = head->next;
    }
}

void free_datalist(data_node_t* head) {
    data_node_t *temp;
    
    while (head != NULL) {
        temp = head;
        free_point(head);
        head = head->next;
        free(temp);
    }
}

/*int search_list(data_node_t *head,char* address,FILE* out_fp) {
    int count = 0;
    data_node_t* temp = head;
    while (temp != NULL) {
        if (strcmp(address,temp->data->address) == 0) {
            print_node(temp,out_fp);
            count++;
            temp = temp->next;
        }
        else {
            temp = temp->next;
        }
    }
    return count;
}*/

/*void print_node(data_node_t* node, FILE*  out_fp) {
    fprintf(out_fp,
    "--> footpath_id: %d || address: %s || clue_sa: %s || asset_type: %s || deltaz: %f || distance: %f || grade1in: %f || mcc_id: %d || mccid_int: %d || rlmax: %f || rlmin: %f || segside: %s || statusid: %d || streetid: %d || street_group: %d || start_lat: %f || start_lon: %f || end_lat: %f || end_lon: %f ||\n"
    ,node->data->footpath_id,node->data->address,node->data->clue_sa,node->data->asset_type,node->data->deltaz,node->data->distance,node->data->grade1in,node->data->mcc_id,node->data->mccid_int,node->data->rlmax,node->data->rlmin,node->data->segside,node->data->statusid,node->data->streetid,node->data->street_group,node->data->start_lat,node->data->start_lon,node->data->end_lat,node->data->end_lon);
}*/
