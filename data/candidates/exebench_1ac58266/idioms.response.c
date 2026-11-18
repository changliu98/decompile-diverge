void max1D_double(double *array, int len, double *max)
{
  int i;
  max[0] = -1.0;
  max[1] = -INFINITY;
  for (i = 0; i < len; i++)
  {
    if (array[i] > max[1])
    {
      max[1] = array[i];
      max[0] = i;
    }
  }
}