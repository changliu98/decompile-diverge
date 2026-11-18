int __cdecl func0(int *tuplex, int size, int value)
{
  int i; // [rsp+0h] [rbp-18h]
  int count; // [rsp+4h] [rbp-14h]

  count = 0;
  for ( i = 0; i < size; ++i )
  {
    if ( tuplex[i] == value )
      ++count;
  }
  return count;
}