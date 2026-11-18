#include <stdio.h>

int set_bit(int *ptr, int n){
 *ptr = *ptr | (1 << n);
 return *ptr;
}
