#include <pthread.h>

#include <stdio.h>

#include <unistd.h>

int test_and_set (int *target)
{
 int rv = *target;
 *target = 1;
 return rv;
}
