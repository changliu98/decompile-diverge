#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <limits.h>

#include <math.h>

short popPriorityQueue(int* size, short* queue){
 *size -= 1;
 return queue[*size * 2];
}
