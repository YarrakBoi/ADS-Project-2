#ifndef DATALIST_H
#define DATALIST_H

#include "datapoint.h"

typedef struct data_node data_node_t;

data_node_t* create_datanode(data_point_t* data);

data_node_t *create_datalist(data_node_t *head, data_point_t* data);

void print_datalist(data_node_t* head);

void free_datalist(data_node_t* head);


#endif