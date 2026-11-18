#include <math.h>

void Calc_Sum_Mean(double Array[], double *Sum, double *Mean)
{
   int i;

   *Sum = 0;
   for (i = 0; i < 100; i++)
      *Sum += Array[i];
   *Mean = *Sum / 100;
}
