float __cdecl func0(float *l, int size)
{
  int i; // [rsp+0h] [rbp-14h]
  float max; // [rsp+4h] [rbp-10h]

  max = -10000.0;
  for ( i = 0; i < size; ++i )
  {
    if ( l[i] > max )
      max = l[i];
  }
  return max;
}