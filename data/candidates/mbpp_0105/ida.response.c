int __cdecl func0(int *lst, int size)
{
  int i; // [rsp+0h] [rbp-14h]
  int total; // [rsp+4h] [rbp-10h]

  total = 0;
  for ( i = 0; i < size; ++i )
    total += lst[i];
  return total;
}