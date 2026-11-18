int __cdecl func0(int *li, int size, int min, int max)
{
  int i; // [rsp+0h] [rbp-1Ch]
  int ctr; // [rsp+4h] [rbp-18h]

  ctr = 0;
  for ( i = 0; i < size; ++i )
  {
    if ( li[i] >= min && li[i] <= max )
      ++ctr;
  }
  return ctr;
}