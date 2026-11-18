int __cdecl func0(int L, int R)
{
  int k; // [rsp+0h] [rbp-14h]
  int count; // [rsp+8h] [rbp-Ch]

  count = 0;
  while ( L <= R )
  {
    if ( L < 10 || L > 15 )
    {
      if ( L > 15 )
      {
        for ( k = L; k; k /= 16 )
        {
          if ( k % 16 >= 10 )
            ++count;
        }
      }
    }
    else
    {
      ++count;
    }
    ++L;
  }
  return count;
}