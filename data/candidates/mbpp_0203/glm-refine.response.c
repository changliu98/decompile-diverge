int __cdecl func0(int n1, int n2)
{
  int setBits = 0;
  int x = n1 ^ n2;

  while (x > 0)
  {
    setBits += x & 1;
    x >>= 1;
  }
  
  return setBits;
}