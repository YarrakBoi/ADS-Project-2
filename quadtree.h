#ifndef QUADTREE_H
#define QUADTREE_H

#include <stdio.h>
#include <stdlib.h>
#include "datapoint.h"
#include "dictionary.h"

typedef enum quadrants quadrants_t;

typedef struct rectangle rectangle_t;

typedef struct quadtree quadtree_t;

enum quadrants determine_quadrants(rectangle_t* bounding_box, point_t* point);

quadtree_t* create_tree(rectangle_t* rectangle);

quadtree_t* insert_node(point_t* new_point, quadtree_t* head, dataDict_t* data);

rectangle_t* create_rectangle(long double bot_left_x,long double bot_left_y,long double top_right_x,long double top_right_y);

rectangle_t* subdivide(rectangle_t* initial,quadrants_t quadrant);

void free_tree(quadtree_t* root);

void search_quadtree(point_t* point, quadtree_t* head, FILE* out_fp);

#endif