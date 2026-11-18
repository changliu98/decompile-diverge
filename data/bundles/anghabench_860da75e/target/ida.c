double __cdecl rel_stddev_stats(double stddev, double avg)
{
  double pct; // [rsp+0h] [rbp-18h]

  pct = 0.0;
  if ( avg != 0.0 )
    return 100.0 * stddev / avg;
  return pct;
}