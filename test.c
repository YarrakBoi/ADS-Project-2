#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include "dictionary.h"
#include "list.h"

//512 char + null byte
#define MAXCHAR 513

//128 char with null byte
#define MAX_FIELD_CHAR 129

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

struct Node {
    dataDict_t* data;
    node_t *next;
};

int main(int argc, char **argv) {
    
    dataDict_t *temp;
    FILE *in_fp = fopen(argv[2],"r");
    FILE *out_fp = fopen(argv[3],"w");
    char row[MAXCHAR];
    char line[MAX_FIELD_CHAR];
    node_t *head = NULL;
    int address_count = 0;

    //assert(in_fp && out_fp);
    assert(in_fp);
    // remove header
    fgets(row, MAXCHAR, in_fp);
    
    //create structs and populate linked list
    while (((temp) = data_dict_read(in_fp)) != NULL) {
        head = create_list(head,temp);
    }

    assert(head != NULL);
    
    //closing after reading required input
    fclose(in_fp);
    
    if(*argv[1] == '1') {
        while(fscanf(stdin,"%[^\n] ",line)!= EOF) {
            fprintf(out_fp,"%s\n",line);
            address_count = search_list(head,line,out_fp);
            if (address_count != 0){
                printf("%s --> %d\n",line,address_count);
                address_count = 0;
            } 
            else {
                printf("%s --> NOTFOUND\n",line);
            }
        }
    }

    free_list(head);
    fclose(out_fp);

    return 0;
}
