void __cdecl std::swap[abi:nn200000]<int>(int *x, int *y)
{
  int temp; // [rsp+0h] [rbp-14h]

  temp = *x;
  *x = *y;
  *y = temp;
}