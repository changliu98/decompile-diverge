#include <stdio.h>

void reverseInt(int* p)
{
 int i;
 for(i=0;i<(10/2);i++)
 {
  int temp = *(p+i);
  *(p+i) = *(p + (10 -i-1));
  *(p + (10 -i-1)) = temp;
 }
}
