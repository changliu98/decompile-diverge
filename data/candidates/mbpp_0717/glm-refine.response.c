double __cdecl func0(double *data, int len)
{
  // Return 0.0 if the array is null or doesn't have enough elements to calculate sample variance
  if (len <= 1)
    return 0.0;

  double mean = avg_calc(data, len);
  double sum_squared_diff = 0.0;

  // Calculate the sum of squared differences from the mean
  for (int i = 0; i < len; ++i)
  {
    double diff = data[i] - mean;
    sum_squared_diff += diff * diff;
  }

  // Calculate and return the sample standard deviation
  return sqrt(sum_squared_diff / (double)(len - 1));
}