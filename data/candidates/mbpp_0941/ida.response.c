int __cdecl func0(int *num, int size)
{
  int i; // [rsp+0h] [rbp-14h]
  int count_elim; // [rsp+4h] [rbp-10h]

  count_elim = 0;
  for ( i = 0; i < size && num[i] != -1; ++i )
    ++count_elim;
  return count_elim;
}