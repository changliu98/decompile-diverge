int __cdecl getPossibleCount(int *ptr, int *num)
{
  int count; // [rsp+0h] [rbp-1Ch]
  int i; // [rsp+8h] [rbp-14h]

  count = 0;
  for ( i = 0; i < 9; ++i )
  {
    if ( ptr[i] )
    {
      ++count;
      if ( num )
        *num = ptr[i];
    }
  }
  return count;
}