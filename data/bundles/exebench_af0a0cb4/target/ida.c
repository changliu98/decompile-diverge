void __cdecl std::swap[abi:nn200000]<int>(int *x, int *y)
{
  int ablage; // [rsp+0h] [rbp-14h]

  ablage = *x;
  *x = *y;
  *y = ablage;
}