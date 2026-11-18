#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <limits.h>

#include <math.h>

void sort4_sorting_network_simple_swap(short* d) {

 {const short a = ((d[0])<(d[1])?(d[0]):(d[1])); const short b = ((d[0])<(d[1])?(d[1]):(d[0])); d[0] = a; d[1] = b;};
 {const short a = ((d[2])<(d[3])?(d[2]):(d[3])); const short b = ((d[2])<(d[3])?(d[3]):(d[2])); d[2] = a; d[3] = b;};
 {const short a = ((d[0])<(d[2])?(d[0]):(d[2])); const short b = ((d[0])<(d[2])?(d[2]):(d[0])); d[0] = a; d[2] = b;};
 {const short a = ((d[1])<(d[3])?(d[1]):(d[3])); const short b = ((d[1])<(d[3])?(d[3]):(d[1])); d[1] = a; d[3] = b;};
 {const short a = ((d[1])<(d[2])?(d[1]):(d[2])); const short b = ((d[1])<(d[2])?(d[2]):(d[1])); d[1] = a; d[2] = b;};

}
