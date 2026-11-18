void mean(double array[], double *sum, double *mean)
{
  int i;
  *sum = 0.0;
  for (i = 0; i < 100; i++)
    *sum += array[i];
  *mean = *sum / 100.0;
}