int __cdecl setLoopIters(double tMin, double tScale, double threshold_hi, unsigned int *NLOOP)
{
  double timeMin; // [rsp+0h] [rbp-28h]

  timeMin = tMin * tScale * (double)(int)*NLOOP;
  if ( timeMin > threshold_hi )
  {
    *NLOOP = (int)((double)(int)*NLOOP * threshold_hi / timeMin);
    if ( *NLOOP < 2 )
      *NLOOP = 2;
  }
  return 0;
}