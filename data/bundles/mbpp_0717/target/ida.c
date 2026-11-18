double __cdecl func0(double *data, int len)
{
  int i; // [rsp+4h] [rbp-2Ch]
  double sd; // [rsp+8h] [rbp-28h]
  double mean; // [rsp+10h] [rbp-20h]

  if ( len <= 1 )
    return 0.0;
  mean = avg_calc(data, len);
  sd = 0.0;
  for ( i = 0; i < len; ++i )
    sd = (data[i] - mean) * (data[i] - mean) + sd;
  return sqrt(sd / (double)(len - 1));
}