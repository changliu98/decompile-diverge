#include <stdio.h>

#include <stdlib.h>

void sum(int c , int *output)
{
 if( output == NULL)
  return ;

 *output = *output + c;

 return;
}
