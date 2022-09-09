#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "dictionary.h"
#include "datapoint.h"


struct Node {
    dataDict_t* data;
    node_t *next;
};

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

node_t *create_node(dataDict_t* data) {
    node_t *temp = (node_t*) malloc(sizeof(*temp));
    node_t *empty_node = NULL;
    assert(temp);
    temp->data = data;
    temp->next = empty_node;
    return temp;
}

node_t *create_list(node_t *head, dataDict_t* data) {
    node_t *iterator = NULL;
    node_t *temp = NULL;

    if(head == NULL){
        temp = create_node(data);
        head = temp;
    }
    else {
        temp = create_node(data);
        iterator = head;
        while (iterator->next != NULL) {
            iterator = iterator->next;
        }
        iterator->next = temp;
        printf("added footpath_id: %d\n", temp->data->footpath_id);
    }
    insertion_sort(&head);
    return head;
}

void print_list(node_t* head) {
    print_data(head->data);
    printf("above is head\n");
    while (head->next != NULL) {
        print_data(head->data);
        printf("break here\n");
        head = head->next;
    }
    printf("end of an iteration\n\n");
}

void free_list(node_t* head) {
    node_t *temp;
    
    while (head != NULL) {
        temp = head;
        free_struct(head->data);
        head = head->next;
        free(temp);
    }
}

int search_list(node_t *head,char* address,FILE* out_fp) {
    int count = 0;
    node_t* temp = head;
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
}

void print_node(node_t* node, FILE*  out_fp) {
    fprintf(out_fp,
    "--> footpath_id: %d || address: %s || clue_sa: %s || asset_type: %s || deltaz: %f || distance: %f || grade1in: %f || mcc_id: %d || mccid_int: %d || rlmax: %f || rlmin: %f || segside: %s || statusid: %d || streetid: %d || street_group: %d || start_lat: %f || start_lon: %f || end_lat: %f || end_lon: %f ||\n"
    ,node->data->footpath_id,node->data->address,node->data->clue_sa,node->data->asset_type,node->data->deltaz,node->data->distance,node->data->grade1in,node->data->mcc_id,node->data->mccid_int,node->data->rlmax,node->data->rlmin,node->data->segside,node->data->statusid,node->data->streetid,node->data->street_group,node->data->start_lat,node->data->start_lon,node->data->end_lat,node->data->end_lon);
}

void print_node_point(node_t* node, FILE* out_fp, point_t* point) {
    fprintf(out_fp,
    "%Lf %Lf\n--> footpath_id: %d || address: %s || clue_sa: %s || asset_type: %s || deltaz: %f || distance: %f || grade1in: %f || mcc_id: %d || mccid_int: %d || rlmax: %f || rlmin: %f || segside: %s || statusid: %d || streetid: %d || street_group: %d || start_lat: %f || start_lon: %f || end_lat: %f || end_lon: %f ||\n"
    ,point->x_coordinate,point->y_coordinate,node->data->footpath_id,node->data->address,node->data->clue_sa,node->data->asset_type,node->data->deltaz,node->data->distance,node->data->grade1in,node->data->mcc_id,node->data->mccid_int,node->data->rlmax,node->data->rlmin,node->data->segside,node->data->statusid,node->data->streetid,node->data->street_group,node->data->start_lat,node->data->start_lon,node->data->end_lat,node->data->end_lon);
}

int node_cmp_grade1in(node_t *a, node_t *b) {
    if (a->data->grade1in < b->data->grade1in) {
        return -1;
    }
    else if (a->data->grade1in > b->data->grade1in) {
        return 1;
    }
    return 0;
}

void insertion_sort(node_t* *head) {
    for (node_t* *current = head; *current != NULL; ) {
        node_t* *sorted = head;
        
        while (*sorted != *current && !( (*current)->data->footpath_id < (*sorted)->data->footpath_id)) {
            sorted = &(*sorted)->next;
        }
        
        if (*sorted != *current) {
            node_t* tmp = *current;
            *current = (*current)->next;
            tmp->next = *sorted;
            *sorted = tmp;
        }
        else {
            current = &(*current)->next;
        }
    }
}

