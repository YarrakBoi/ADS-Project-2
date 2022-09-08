#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include "quadtree.h"
#include "dictionary.h"

//0 for SW,1 for SE, 2 for NE, 3 for NW
enum quadrants{SW = 0, SE = 1, NE = 2, NW = 3};

struct point2d {
    long double x_coordinate;
    long double y_coordinate;
    dataDict_t* info;
};

struct rectangle {
    long double bot_left_x;
    long double bot_left_y;
    long double top_right_x;
    long double top_right_y;
};

struct quadtree {
    bool is_internal_root;
    rectangle_t* bounding_box;
    point_t* point;
    quadtree_t* NW;
    quadtree_t* NE;
    quadtree_t* SW;
    quadtree_t* SE;
};

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

quadtree_t* create_tree(rectangle_t* rectangle) {
    quadtree_t* temp = (quadtree_t*) malloc(sizeof(*temp));
    assert(temp);
    temp->is_internal_root = false;
    temp->bounding_box = rectangle;
    temp->point = NULL;
    temp->NE = NULL;
    temp->NW = NULL;
    temp->SE = NULL;
    temp->SW = NULL;
    return temp;
}

bool in_bounding(point_t* P,rectangle_t* bounding_box) {
    return (P->x_coordinate >= bounding_box->bot_left_x && P->x_coordinate < bounding_box->top_right_x
    && P->y_coordinate >= bounding_box->bot_left_y && P->y_coordinate < bounding_box->top_right_y);
}

quadrants_t determine_quadrants(rectangle_t* bounding_box, point_t* point) {
    long double rectangle_length = fabs(bounding_box->bot_left_x - bounding_box->top_right_x);
    long double rectangle_height = fabs(bounding_box->bot_left_y - bounding_box->top_right_y);
    long double rectangle_center_x = bounding_box->bot_left_x + (rectangle_length/2);
    long double rectangle_center_y = bounding_box->bot_left_y + (rectangle_height/2);
    quadrants_t quadrant;
    if (point->x_coordinate >= bounding_box->bot_left_x && point->x_coordinate < rectangle_center_x) {
        if (point->y_coordinate >= bounding_box->bot_left_y && point->y_coordinate < rectangle_center_y) {
            //return SW here
            quadrant = SW;
        }
        else if (point->y_coordinate >= rectangle_center_y && point->y_coordinate < bounding_box->top_right_y) { 
            //return NW here
            quadrant = NW;
        }
    }
    else if(point->x_coordinate >= rectangle_center_x && point->x_coordinate < bounding_box->top_right_x) {
        if (point->y_coordinate >= bounding_box->bot_left_y && point->y_coordinate < rectangle_center_y) {
            //return SE here
            quadrant = SE;
        }
        else if (point->y_coordinate >= rectangle_center_y && point->y_coordinate < bounding_box->top_right_y) { 
            //return NE here
            quadrant = NE;
        }
    }
    return quadrant;
}

rectangle_t* create_rectangle(long double bot_left_x,long double bot_left_y,long double top_right_x,long double top_right_y) {
    rectangle_t* temp = (rectangle_t*) malloc(sizeof(*temp));
    assert(temp);
    temp->bot_left_x = bot_left_x;
    temp->bot_left_y = bot_left_y;
    temp->top_right_x = top_right_x;
    temp->top_right_y = top_right_y;
    return temp;
}

quadtree_t* insert_node(point_t* new_point, quadtree_t* head) {
    if (head->is_internal_root == false) {
    //if root is empty, just insert 
        if (in_bounding(new_point,head->bounding_box)) {
            if (head->point == NULL) { // CASE WHITE NODE
                head->point = new_point;
            }
            else if(head->point != NULL) { // CASE BLACK NODE
                //move root point to new root
                point_t* old_point = head->point;
                head->point = NULL;
                head->is_internal_root = true;
                quadrants_t old_quadrant = determine_quadrants(head->bounding_box, old_point); 
                switch(old_quadrant){
                    case SW:
                        head->SW = create_tree(subdivide(head->bounding_box, old_quadrant));
                        head->SW->point = old_point;
                        break;
                    case NW:
                        head->NW = create_tree(subdivide(head->bounding_box, old_quadrant));
                        head->NW->point = old_point;
                        break;
                    case NE:
                        head->NE = create_tree(subdivide(head->bounding_box, old_quadrant));
                        head->NE->point = old_point;
                        break;
                    case SE:
                        head->SE = create_tree(subdivide(head->bounding_box, old_quadrant));
                        head->SE->point = old_point;
                        break;        
                }
                quadrants_t new_quadrant = determine_quadrants(head->bounding_box, new_point);
                if (old_quadrant != new_quadrant){
                    switch(new_quadrant){
                    case SW:
                        head->SW = create_tree(subdivide(head->bounding_box, new_quadrant));
                        head->SW->point = new_point;
                        break;
                    case NW:
                        head->NW = create_tree(subdivide(head->bounding_box, new_quadrant));
                        head->NW->point = new_point;
                        break;
                    case NE:
                        head->NE = create_tree(subdivide(head->bounding_box, new_quadrant));
                        head->NE->point = new_point;
                        break;
                    case SE:
                        head->SE = create_tree(subdivide(head->bounding_box, new_quadrant));
                        head->SE->point = new_point;
                        break;        
                    }
                }
            }
        }
    }
    else if (head->is_internal_root == true && head->point == NULL) { // CASE GREY
            quadrants_t new_quadrant = determine_quadrants(head->bounding_box, new_point);
            switch(new_quadrant){
                case SW:
                    if(head->SW == NULL) {
                        head->SW = create_tree(subdivide(head->bounding_box, new_quadrant));
                    }
                    insert_node(new_point,head->SW);
                    break;
                case NW:
                    if(head->NW == NULL) {
                        head->NW = create_tree(subdivide(head->bounding_box, new_quadrant));
                        }
                    insert_node(new_point, head->NW);
                    break;
                case NE:
                    if(head->NE == NULL) {
                        head->NE = create_tree(subdivide(head->bounding_box, new_quadrant));
                    }
                    insert_node(new_point, head->NE);
                    break;
                case SE:
                    if(head->NE == NULL) {
                        head->NE = create_tree(subdivide(head->bounding_box, new_quadrant));
                    }
                    insert_node(new_point, head->SE);
                    break;  
            }
        }
    return head;
}

rectangle_t* subdivide(rectangle_t* initial,quadrants_t quadrant) {
    rectangle_t* rect_temp = malloc(sizeof(*rect_temp));
    long double length = fabs(initial->top_right_x - initial->bot_left_x);
    long double height = fabs(initial->top_right_y - initial->bot_left_y);
    long double center_y = initial->bot_left_y + (height/2);
    long double center_x = initial->bot_left_x + (length/2);
    switch (quadrant){
        case SW:
            rect_temp = create_rectangle(initial->bot_left_x, initial->bot_left_y, center_x, center_y);
            break;
        case NW:
            rect_temp = create_rectangle(initial->bot_left_x, center_y, center_x, initial->top_right_y);
            break;
        case NE:
            rect_temp = create_rectangle(center_x, center_y, initial->top_right_x, initial->top_right_y);
            break;
        case SE:
            rect_temp = create_rectangle(center_x, initial->bot_left_y, initial->top_right_x, center_y);
            break;
    }
    return rect_temp;
}
