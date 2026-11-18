void __cdecl std::swap[abi:nn200000]<int>(int *a, int *b)
{
  int t; // [rsp+0h] [rbp-14h]

  t = *a;
  *a = *b;
  *b = t;
}