int __cdecl func0(int n)
{
  int temp; // [rsp+0h] [rbp-10h]
  int res; // [rsp+4h] [rbp-Ch]
  int count; // [rsp+8h] [rbp-8h]

  count = 0;
  res = 0;
  for ( temp = n; temp > 0; temp >>= 1 )
  {
    if ( !(count % 2) )
      res |= 1 << count;
    ++count;
  }
  return res | n;
}