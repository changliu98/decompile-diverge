int __cdecl func0(int *list, int size)
{
  int i; // [rsp+0h] [rbp-14h]
  int res; // [rsp+4h] [rbp-10h]

  res = 0;
  for ( i = 0; i < size; ++i )
    res = list[i] + 10 * res;
  return res;
}