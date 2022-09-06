#ifndef QUADTREE_H
#define QUADTREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct rectangle rectangle_t;

typedef struct quadtree quad_t;

typedef struct point2d point_t;

int determine_quadrants(rectangle_t bounding_box, point_t point);

quad_t* create_node(long double latitude_y,long double longitude_x,long double bot_left_x,long double bot_left_y,long double top_right_x,long double top_right_y);

point_t* create_point(long double x_coordinate, long double y_coordinate);

rectangle_t* create_rectangle(long double bot_left_x,long double bot_left_y,long double top_right_x,long double top_right_y);

void free_node(quad_t* root);

#endif