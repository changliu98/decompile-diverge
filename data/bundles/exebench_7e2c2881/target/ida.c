int __cdecl getPossibleCount(int *ptr, int *num)
{
  int count; // [rsp+4h] [rbp-18h]
  int i; // [rsp+8h] [rbp-14h]

  count = 0;
  for ( i = 0; i < 9; ++i )
  {
    if ( ptr[i] )
    {
      ++count;
      *num = ptr[i];
    }
  }
  return count;
}