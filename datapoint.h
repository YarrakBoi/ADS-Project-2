//header for data point and point2d structs and functions

#ifndef DATA_POINT_H
#define DATA_POINT_H

#include "dictionary.h"
#include "list.h"

typedef struct point2d point_t;

typedef struct data_point data_point_t;

point_t* create_point(long double x,long double y);

data_point_t* create_data_point(node_t* node_info);


#endif