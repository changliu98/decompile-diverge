int __cdecl func0(int *list1, int size)
{
  int i; // [rsp+0h] [rbp-14h]
  int max; // [rsp+4h] [rbp-10h]

  max = *list1;
  for ( i = 0; i < size; ++i )
  {
    if ( list1[i] < max )
      max = list1[i];
  }
  return max;
}