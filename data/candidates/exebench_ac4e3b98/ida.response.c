void __cdecl std::swap[abi:nn200000]<int>(unsigned int *p, unsigned int *q)
{
  unsigned int x; // [rsp+0h] [rbp-14h]

  x = *p;
  *p = *q;
  *q = x;
}