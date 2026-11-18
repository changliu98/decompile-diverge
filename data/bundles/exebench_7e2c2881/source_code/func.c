#include <stdio.h>

#include <stdlib.h>

#include <string.h>

int getPossibleCount(int ptr[], int *num)
{
    int i;
    int count = 0;
    int size = 3*3;
    for (i = 0; i < size; i++)
    {
        if (ptr[i] != 0)
        {
            count++;
            *num = ptr[i];
        }
    }
    return count;
}
