#include <stdlib.h>

#include <unistd.h>

#include <limits.h>

#include <errno.h>

#include <math.h>

#include <stdio.h>

#include <assert.h>

#include <string.h> // for strcmp

#include <sys/time.h>

void swap_l ( long * a, long * b ) { long tmp = *a; *a = *b; *b = tmp; }
