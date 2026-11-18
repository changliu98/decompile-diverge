int countSetBits(int x, int y)
{
  int z = x ^ y;
  int setBits = 0;
  while (z > 0)
  {
    setBits += z & 1;
    z >>= 1;
  }
  return setBits;
}