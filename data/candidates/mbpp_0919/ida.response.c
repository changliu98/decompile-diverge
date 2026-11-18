int __cdecl func0(int *items, int length)
{
  int i; // [rsp+0h] [rbp-14h]
  int tot; // [rsp+4h] [rbp-10h]

  tot = 1;
  for ( i = 0; i < length; ++i )
    tot *= items[i];
  return tot;
}