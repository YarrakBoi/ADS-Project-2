#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdio.h>
#include <stdbool.h>

typedef struct dataDict dataDict_t;

//fill in the struct's fields according to the number of commas read
void fill_in_field(char* string_to_be_copied,dataDict_t *dataDict,int num_fields_read);

dataDict_t *data_dict_read(FILE *f);

// skip the header line of .csv file "f", workshop week 2 q 6
void skip_header(FILE *f);

void free_struct(dataDict_t *d);

void print_data(dataDict_t* data);

//return 1 if address given is the same as the address in the node
int compare_address(char *address,char* address1);


#endif
