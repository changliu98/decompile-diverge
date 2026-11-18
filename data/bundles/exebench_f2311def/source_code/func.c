#include <stdio.h>

#include <stddef.h>

#include <stdlib.h>

int INDMAXVAL(float val[], int i1, int i2)
{



  int i, ini;

  ini = i1;
  for(i = i1+1; i <= i2; i++) {
    if(val[ini] < val[i])
      ini = i;
  }
  return(ini);
}
