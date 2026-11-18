int __cdecl func0(int n)
{
  int temp; // [rsp+0h] [rbp-10h]
  int count; // [rsp+4h] [rbp-Ch]
  int res; // [rsp+8h] [rbp-8h]

  res = 0;
  count = 0;
  for ( temp = n; temp > 0; temp >>= 1 )
  {
    if ( !(count % 2) )
      res |= 1 << count;
    ++count;
  }
  return res ^ n;
}