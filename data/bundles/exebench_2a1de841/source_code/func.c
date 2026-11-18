#include <math.h>

#include <stdlib.h>

double linsched_rand(unsigned int *const state)
{
 unsigned int rand = (16807 * (*state)) % 2147483647;
 *state = rand;
 return rand / (double) 2147483647;
}
