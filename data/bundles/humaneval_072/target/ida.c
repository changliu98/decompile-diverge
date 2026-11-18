bool __cdecl func0(int *q, int size, int w)
{
  int i; // [rsp+10h] [rbp-20h]
  int sum; // [rsp+14h] [rbp-1Ch]

  sum = 0;
  for ( i = 0; i < size / 2; ++i )
  {
    if ( q[i] != q[size - 1 - i] )
      return 0;
    sum += q[size - 1 - i] + q[i];
  }
  if ( size % 2 == 1 )
    sum += q[size / 2];
  return sum <= w;
}