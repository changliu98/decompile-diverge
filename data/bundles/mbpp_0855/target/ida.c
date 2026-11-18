bool __cdecl func0(int x)
{
  int parity; // [rsp+0h] [rbp-8h]

  parity = 0;
  while ( x )
  {
    x &= x - 1;
    ++parity;
  }
  return parity % 2 == 0;
}