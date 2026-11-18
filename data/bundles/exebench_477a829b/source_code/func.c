#include <stdio.h>

void swap(int *const ptrX, int *const ptrY) {
 int temp = *ptrX;

 *ptrX = *ptrY;
 *ptrY = temp;
}
