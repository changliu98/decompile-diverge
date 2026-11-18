#include <stdio.h>

#include <stdlib.h>

void swap(int *left, int *right){
    int temp;
    temp = *left;
    *left = *right;
    *right = temp;
}
