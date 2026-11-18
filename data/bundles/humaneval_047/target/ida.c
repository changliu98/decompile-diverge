float __cdecl func0(float *l, int size)
{
  float temp; // [rsp+18h] [rbp-20h]
  int j; // [rsp+1Ch] [rbp-1Ch]
  int i; // [rsp+20h] [rbp-18h]

  for ( i = 0; i < size; ++i )
  {
    for ( j = i + 1; j < size; ++j )
    {
      if ( l[i] > l[j] )
      {
        temp = l[i];
        l[i] = l[j];
        l[j] = temp;
      }
    }
  }
  if ( size % 2 == 1 )
    return l[size / 2];
  return 0.5 * (float)(l[size / 2] + l[size / 2 - 1]);
}