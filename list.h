#ifndef LIST_H
#define LIST_H

#include "dictionary.h"

typedef struct Node node_t;

node_t *create_list(node_t* head,dataDict_t* data);

node_t *create_node(dataDict_t* data);

int search_list(node_t *head,char* address,FILE* out_fp);

void print_list(node_t* head);

void free_list(node_t* node);

void print_node(node_t* node,FILE*  out_fp);

// compares 2 nodes "a" and "b" by grade1in, returns -1, 0, +1 for <, =, > W3.8 
int node_cmp_grade1in(node_t *a, node_t *b);

#endif
