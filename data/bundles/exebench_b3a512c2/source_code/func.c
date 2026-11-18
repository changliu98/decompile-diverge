#include <stdio.h>

#include <stdlib.h>

#include <string.h>

int getPossibleCount(int ptr[], int *num)
{
    int i;
    int size = 3*3;
    int count = 0;

    for (i = 0; i < size; i++)
    {
        if (ptr[i] != 0)
        {
            count++;
            if (num)
            {
                *num = ptr[i];
            }
        }
    }

    return count;
}
