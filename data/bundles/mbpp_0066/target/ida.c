int __cdecl func0(int *list, int list_size)
{
  int i; // [rsp+0h] [rbp-14h]
  int pos_count; // [rsp+4h] [rbp-10h]

  pos_count = 0;
  for ( i = 0; i < list_size; ++i )
  {
    if ( list[i] >= 0 )
      ++pos_count;
  }
  return pos_count;
}