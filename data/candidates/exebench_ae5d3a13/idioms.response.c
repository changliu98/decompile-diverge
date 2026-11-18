void sum(double *data, int len, double *ret)
{
  int i;
  double sum = 0.;
  for (i = 0; i < len; i++)
    sum += data[i];
  *ret = sum;
}