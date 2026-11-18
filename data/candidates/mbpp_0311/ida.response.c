int __cdecl func0(int n)
{
  char count; // [rsp+0h] [rbp-14h]
  int temp; // [rsp+4h] [rbp-10h]
  char pos; // [rsp+8h] [rbp-Ch]

  if ( ((n + 1) & n) == 0 )
    return n;
  pos = 0;
  temp = n;
  count = 0;
  while ( temp )
  {
    if ( (temp & 1) == 0 )
      pos = count;
    ++count;
    temp >>= 1;
  }
  return (1 << pos) | n;
}