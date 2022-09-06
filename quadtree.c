#include <stdbool.h>
#include <math.h>
#include "quadtree.h"
#include "dictionary.h"
#include "datapoint.h"

//0 for SW,1 for SE, 2 for NE, 3 for NW
enum quadrants{SW = 0, SE = 1, NE = 2, NW = 3};

struct rectangle {
    long double bot_left_x;
    long double bot_left_y;
    long double top_right_x;
    long double top_right_y;
};

