int __cdecl func0(int *lst, int size)
{
  int i; // [rsp+0h] [rbp-14h]
  int sum; // [rsp+4h] [rbp-10h]

  sum = 0;
  for ( i = 0; 2 * i + 1 < size; ++i )
  {
    if ( !(lst[2 * i + 1] % 2) )
      sum += lst[2 * i + 1];
  }
  return sum;
}