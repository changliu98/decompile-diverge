int __cdecl func0(int *list1, int size)
{
  int i; // [rsp+0h] [rbp-18h]

  for ( i = 0; i < size; ++i )
  {
    if ( list1[i] < 0 )
      return list1[i];
  }
  return 0;
}