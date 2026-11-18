double rel_stddev_stats(double stddev, double avg)
{
 double pct = 0.0;
 if (avg)
  pct = (stddev / avg) * 100.0;
 return pct;
}