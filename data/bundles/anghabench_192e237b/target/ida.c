double __cdecl estLog(double N)
{
  double x; // [rsp+0h] [rbp-18h]
  double logN; // [rsp+8h] [rbp-10h]

  logN = 1.0;
  for ( x = 10.0; N > x; x = 10.0 * x )
    logN = logN + 1.0;
  return logN;
}