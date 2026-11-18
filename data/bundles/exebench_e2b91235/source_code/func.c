#include <stdio.h>

#include <string.h>

#include <math.h>

#include <stdlib.h>

#include <assert.h>

#include <stdbool.h>

int num_to_array(int *arr, int num)
{
    int digit, i = 0;

    while (num > 0) {
        digit = num % 10;

        arr[i++] = digit;

        num /= 10;
    }

    return i;
}
