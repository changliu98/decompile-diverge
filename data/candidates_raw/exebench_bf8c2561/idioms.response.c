double check(double *data, long sizeMB)
{
  unsigned long i;
  unsigned long n = sizeMB / sizeof(double);
  double sum = 0.0;
  for (i = 0; i < n; i++)
    sum += data[i];
  data[0] = sum / n;
  return (sum);
}