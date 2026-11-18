void __cdecl sum(double *a, int len, double *retVal)
{
  int i; // [rsp+0h] [rbp-24h]
  double acc; // [rsp+4h] [rbp-20h]

  acc = 0.0;
  for ( i = 0; i < len; ++i )
    acc = a[i] + acc;
  *retVal = acc;
}