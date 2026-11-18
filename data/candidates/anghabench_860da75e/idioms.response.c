static double rel_stddev_stats(double stddev, double avg)
{
  double pct = 0.0;
  if (avg != 0.0)
    pct = (stddev * 100.0) / avg;
  return pct;
}