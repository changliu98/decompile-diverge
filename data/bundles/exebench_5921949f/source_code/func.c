#include <stdio.h>

void factorial(double fact[])
{
# 50 "printfact5.c"
  int count;

  fact[0] = 1.;


  for (count = 0; count < 20; ++count)
    fact[count+1] = (double)(count+1) * fact[count];

  return;

}
