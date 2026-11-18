static double get_stddev_pct(double stddev, double avg)
{
  double pct = 0.0;
  if (avg != 0.0)
    pct = (stddev * 100.0) / avg;
  return pct;
}