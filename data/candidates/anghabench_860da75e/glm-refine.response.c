double rel_stddev_stats(double stddev, double avg)
{
  if (avg != 0.0)
    return 100.0 * stddev / avg;
  
  return 0.0;
}