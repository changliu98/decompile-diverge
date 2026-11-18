void __cdecl maxind(double *segmentToAnalyze, int length, double *maximum, double *index)
{
  int i; // [rsp+0h] [rbp-24h]

  *maximum = *segmentToAnalyze;
  *index = 0.0;
  for ( i = 1; i < length; ++i )
  {
    if ( segmentToAnalyze[i] > *maximum )
    {
      *maximum = segmentToAnalyze[i];
      *index = 1.0 * (double)i;
    }
  }
}