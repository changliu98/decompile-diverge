int __cdecl func0(int *lst, int size)
{
  int v2; // eax
  int i; // [rsp+0h] [rbp-14h]
  int sum; // [rsp+4h] [rbp-10h]

  sum = 0;
  for ( i = 0; i < size; ++i )
  {
    if ( i % 3 )
    {
      if ( i % 4 )
        v2 = lst[i];
      else
        v2 = lst[i] * lst[i] * lst[i];
      sum += v2;
    }
    else
    {
      sum += lst[i] * lst[i];
    }
  }
  return sum;
}