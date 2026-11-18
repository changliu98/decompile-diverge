#include <stdio.h>

#include <stdlib.h>

void swap (int *left, int *right)
{
 int tmp = *left;
 *left = *right;
 *right = tmp;
}
