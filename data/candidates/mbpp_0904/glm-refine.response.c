bool __cdecl func0(int x)
{
  // Checks if the least significant bit is 0, which is equivalent to x % 2 == 0
  return (x & 1) == 0;
}