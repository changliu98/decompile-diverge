int __cdecl func0(int *dict, int size)
{
  int i; // [rsp+0h] [rbp-14h]
  int sum; // [rsp+4h] [rbp-10h]

  sum = 0;
  for ( i = 0; i < size; ++i )
    sum += dict[i];
  return sum;
}