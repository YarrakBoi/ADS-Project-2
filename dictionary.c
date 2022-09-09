#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#include "dictionary.h"

//512 char + null byte
#define MAXCHAR 513

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

//fill in the struct's fields according to the number of commas read
void fill_in_field(char* string_to_be_copied, dataDict_t* dataDict, int num_fields_read) {
    switch (num_fields_read) {
        case 1:
        //convert string to base 10 int
            dataDict->footpath_id = strtol(string_to_be_copied,NULL,10);
            break;
        case 2:
        //duplicate string 
            dataDict->address = strdup(string_to_be_copied);
            break;
        case 3:
            dataDict->clue_sa = strdup(string_to_be_copied);
            break;
        case 4:
            dataDict->asset_type = strdup(string_to_be_copied);
            break;
        case 5:
        //covert string to double
            dataDict->deltaz = strtod(string_to_be_copied,NULL);
            break;
        case 6:
            dataDict->distance = strtod(string_to_be_copied,NULL);
            break;
        case 7:
            dataDict->grade1in = strtod(string_to_be_copied,NULL);
            break;
        case 8:
            dataDict->mcc_id = strtol(string_to_be_copied,NULL,10);
            break;
        case 9:
            dataDict->mccid_int = strtol(string_to_be_copied,NULL,10);
            break;
        case 10:
            dataDict->rlmax = strtod(string_to_be_copied,NULL);
            break;
        case 11:
            dataDict->rlmin = strtod(string_to_be_copied,NULL);
            break;
        case 12:
            dataDict->segside = strdup(string_to_be_copied);
            break;
        case 13:
            dataDict->statusid = strtol(string_to_be_copied,NULL,10);
            break;
        case 14:
            dataDict->streetid = strtol(string_to_be_copied,NULL,10);
            break;
        case 15:
            dataDict->street_group = strtol(string_to_be_copied,NULL,10);
            break;
        case 16:
            dataDict->start_lat = strtod(string_to_be_copied,NULL);
            break;
        case 17:
            dataDict->start_lon = strtod(string_to_be_copied,NULL);
            break;
        case 18:
            dataDict->end_lat = strtod(string_to_be_copied,NULL);
            break;
        case 19:
            dataDict->end_lon = strtod(string_to_be_copied,NULL);
            break; 
    }
}

// skip the header line of .csv file "f", workshop week 2 q 6
void skip_header(FILE *f) {
	while (fgetc(f) != '\n');
}


dataDict_t *data_dict_read(FILE *f) {
	dataDict_t *d = NULL;
    char *ptr;
    char row[MAXCHAR];
    // length of the targeted string
    int str_count = 0;
    // position of line
    int line_count = 0;
    // position of the first char read after a comma or start of line
    int first_char_pos = 0;
    // has the first alphanum character been saved
    bool pos_is_saved = false;
    // check if double quote are read
    bool quote_detected = false;
    // read in comma
    bool read_in_comma = false;
    // number of field transversed
    int fields_read = 0;
	if (fgets(row,MAXCHAR,f) != NULL) {
		d = malloc(sizeof(*d));
		assert(d);
		// parse through file and save string read
        for (; line_count < strlen(row); line_count++) {
            //reads in comma when a double quote is detected
            if(quote_detected == true){
                if(row[line_count] == ',') {
                    str_count++;
                    quote_detected = false;
                    read_in_comma = true;
                    continue;
                }
            }
            
            if((line_count >= 1 && row[line_count-1] == ',') && row[line_count] == '\"') {
                quote_detected = true;
            }
            // if it detects accepted char, count how many char until the next comma
            // and save the position of the first char read
            
            else if (row[line_count] == ',' || row[line_count] == '\n') {
                fields_read++;
                // when comma is encountered, stop counting the length of string
                // set an array and append each char followed with \0 at the end
                ptr = malloc(sizeof(char) * str_count + 1);
                for (int i = 0; i <= str_count; i++, first_char_pos++) {
                    if(row[first_char_pos] == ',' && read_in_comma) {
                        ptr[i] = row[first_char_pos];
                        read_in_comma = false;
                        continue;
                    }
                    if(row[first_char_pos] == '\"') {
                        ptr[i] = '\0';
                        break;
                    }
                    if (i == str_count) {
                        ptr[i] = '\0';
                        break;
                    }
                    else {
                        ptr[i] = row[first_char_pos];
                    }
                }
                first_char_pos = 0;
                str_count = 0;
                pos_is_saved = false;
                quote_detected = false;
                fill_in_field(ptr, d, fields_read);
                free(ptr);
                continue;
            }
            else {
                if (pos_is_saved == false) {
                    first_char_pos = line_count;
                    pos_is_saved = true;
                }
                str_count++;
            }
        }
	}
	return d;
}

void print_data(dataDict_t* data) {
    printf("head footpath_id is %d\n", data->footpath_id);
}

void free_struct(dataDict_t *d) {
    free(d->address);
    free(d->clue_sa);
    free(d->asset_type);
    free(d->segside);
    free(d);
}



