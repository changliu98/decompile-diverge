void __cdecl Calc_Sum_Mean(double *Array, double *Sum, double *Mean)
{
  const int ARRAY_SIZE = 100;
  double total_sum = 0.0;

  for (int i = 0; i < ARRAY_SIZE; ++i)
  {
    total_sum += Array[i];
  }

  *Sum = total_sum;
  *Mean = total_sum / ARRAY_SIZE;
}