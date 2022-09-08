#ifndef DATA_POINT_H
#define DATA_POINT_H

#include "dictionary.h"

typedef struct point2d point_t;

point_t* create_point(long double x, long double y, dataDict_t* info);

void print_point(point_t* data);

void free_point(point_t* d);


#endif