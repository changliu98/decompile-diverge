#include <stdlib.h>

#include <stdint.h>

#include <string.h>

#include <math.h>

#include <limits.h>

#include <pthread.h>

static int mean3(int a, int b, int c, int white, int* err)
{
    int m = (a + b + c) / 3;

    if (err)
        *err = ((((((((a - m) > 0 ? (a - m) : -(a - m)))>(((b - m) > 0 ? (b - m) : -(b - m))))?(((a - m) > 0 ? (a - m) : -(a - m))):(((b - m) > 0 ? (b - m) : -(b - m)))))>(((c - m) > 0 ? (c - m) : -(c - m))))?((((((a - m) > 0 ? (a - m) : -(a - m)))>(((b - m) > 0 ? (b - m) : -(b - m))))?(((a - m) > 0 ? (a - m) : -(a - m))):(((b - m) > 0 ? (b - m) : -(b - m))))):(((c - m) > 0 ? (c - m) : -(c - m))));

    if (a >= white || b >= white || c >= white)
        return (((m)>(white))?(m):(white));

    return m;
}
