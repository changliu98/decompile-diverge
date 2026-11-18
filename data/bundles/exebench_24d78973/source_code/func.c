#include <stdlib.h>

#include <stdio.h>

static void swap(int *x,int *y){
 int temp;

 temp=*x;
 *x=*y;
 *y=temp;
}
