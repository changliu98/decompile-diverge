void __cdecl func0(int num, int *result)
{
  int odd_count; // [rsp+8h] [rbp-18h]
  int even_count; // [rsp+Ch] [rbp-14h]
  int numa; // [rsp+1Ch] [rbp-4h]

  even_count = 0;
  odd_count = 0;
  numa = abs(num);
  do
  {
    if ( numa % 10 % 2 )
      ++odd_count;
    else
      ++even_count;
    numa /= 10;
  }
  while ( numa > 0 );
  *result = even_count;
  result[1] = odd_count;
}