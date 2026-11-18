void __cdecl Calc_Sum_Mean(double *Array, double *Sum, double *Mean)
{
  int i; // [rsp+0h] [rbp-1Ch]

  *Sum = 0.0;
  for ( i = 0; i < 100; ++i )
    *Sum = Array[i] + *Sum;
  *Mean = *Sum / 100.0;
}