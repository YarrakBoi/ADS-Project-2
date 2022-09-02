#ifndef QUADTREE_H
#define QUADTREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct rectangle rectangle_t;

typedef struct node node_t;

rectangle_t *create_rectangle(long double bot_left_x,long double bot_left_y,long double top_right_x,long double top_right_y);

void free_node(node_t * root);

#endif