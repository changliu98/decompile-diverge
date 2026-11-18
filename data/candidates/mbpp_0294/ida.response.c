int __cdecl func0(int *listval, int size)
{
  int i; // [rsp+0h] [rbp-14h]
  signed int max_val; // [rsp+4h] [rbp-10h]

  max_val = 0x80000000;
  for ( i = 0; i < size; ++i )
  {
    if ( listval[i] > max_val )
      max_val = listval[i];
  }
  return max_val;
}