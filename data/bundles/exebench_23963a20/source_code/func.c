#include <stdio.h>

#include <stdlib.h>

static void swap(int *lhs, int *rhs)
{
 int temp = *lhs;
 *lhs = *rhs;
 *rhs = temp;
}
