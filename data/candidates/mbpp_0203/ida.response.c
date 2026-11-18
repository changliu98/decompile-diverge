int __cdecl func0(int n1, int n2)
{
  int setBits; // [rsp+0h] [rbp-10h]
  int x; // [rsp+4h] [rbp-Ch]

  x = n2 ^ n1;
  setBits = 0;
  while ( x > 0 )
  {
    setBits += x & 1;
    x >>= 1;
  }
  return setBits;
}