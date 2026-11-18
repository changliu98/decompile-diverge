void __cdecl std::swap[abi:nn200000]<int>(unsigned int *a, unsigned int *b)
{
  unsigned int c; // [rsp+0h] [rbp-14h]

  c = *a;
  *a = *b;
  *b = c;
}