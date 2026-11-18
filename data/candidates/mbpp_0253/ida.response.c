int __cdecl func0(int *list1, int length)
{
  int i; // [rsp+0h] [rbp-14h]
  int ctr; // [rsp+4h] [rbp-10h]

  ctr = 0;
  for ( i = 0; i < length; ++i )
    ++ctr;
  return ctr;
}