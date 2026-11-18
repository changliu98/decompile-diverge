double rel_stddev_stats(double stddev,double avg)

{
  double pct;
  double avg_local;
  double stddev_local;
  
  pct = 0.0;
  if ((avg != 0.0) || (NAN(avg))) {
    pct = (DAT_00102008 * stddev) / avg;
  }
  return pct;
}