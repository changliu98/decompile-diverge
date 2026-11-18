void __cdecl fancySwap(int *first, int *second)
{
  *first ^= *second;
  *second ^= *first;
  *first ^= *second;
}