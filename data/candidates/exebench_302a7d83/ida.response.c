void __cdecl std::swap[abi:nn200000]<int>(int *x, int *y)
{
  int t; // [rsp+0h] [rbp-14h]

  t = *x;
  *x = *y;
  *y = t;
}