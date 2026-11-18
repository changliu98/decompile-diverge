int __cdecl func0(int *list, int list_size)
{
  int i; // [rsp+0h] [rbp-14h]
  int neg_count; // [rsp+4h] [rbp-10h]

  neg_count = 0;
  for ( i = 0; i < list_size; ++i )
  {
    if ( list[i] <= 0 )
      ++neg_count;
  }
  return neg_count;
}