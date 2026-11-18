double stddev_calc(double *data, int len)
{
  if (len < 2)
    return 0.0;
  double mean = avg_calc(data, len);
  double sum = 0.0;
  int i;
  for (i = 0; i < len; i++)
    sum += (data[i] - mean)*(data[i] - mean);
  return sqrt(sum / (len - 1));
}