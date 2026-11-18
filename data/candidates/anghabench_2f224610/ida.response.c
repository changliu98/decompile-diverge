bool __cdecl is_dup(int *seq, int index, int val)
{
  int i; // [rsp+0h] [rbp-1Ch]

  for ( i = 0; i < index; ++i )
  {
    if ( seq[i] == val )
      return 1;
  }
  return 0;
}