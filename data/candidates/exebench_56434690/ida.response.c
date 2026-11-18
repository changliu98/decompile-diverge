void __cdecl std::swap[abi:nn200000]<int>(int *m, int *n)
{
  int x; // [rsp+0h] [rbp-14h]

  x = *m;
  *m = *n;
  *n = x;
}