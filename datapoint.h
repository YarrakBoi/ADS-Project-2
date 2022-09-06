//header for data point and point2d structs and functions

#ifndef DATA_POINT_H
#define DATA_POINT_H

#include "dictionary.h"
#include "list.h"

typedef struct point2d point_t;

typedef struct data_point data_point_t;

point_t* create_point(long double x,long double y);

data_point_t* create_data_point(dataDict_t* dataDict);

void print_point(point_t* data);

void print_datapoint(data_point_t* data);

void free_point(data_point_t* d);


#endif