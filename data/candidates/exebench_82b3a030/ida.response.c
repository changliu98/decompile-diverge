int __cdecl intwt(double N, double *W)
{
  int i; // [rsp+0h] [rbp-14h]

  if ( N >= 1.0 )
  {
    i = (int)N;
    *W = 1.0;
  }
  else
  {
    i = 1;
    *W = N;
  }
  return i;
}