void __cdecl func0(int startnum, int endnum, int *result, int *result_size)
{
  int temp; // [rsp+4h] [rbp-24h]
  bool divisible; // [rsp+Bh] [rbp-1Dh]

  *result_size = 0;
  while ( startnum <= endnum )
  {
    divisible = 1;
    for ( temp = startnum; temp > 0; temp /= 10 )
    {
      if ( !(temp % 10) || startnum % (temp % 10) )
      {
        divisible = 0;
        break;
      }
    }
    if ( divisible )
      result[(*result_size)++] = startnum;
    ++startnum;
  }
}