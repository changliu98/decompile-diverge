void __cdecl std::swap[abi:nn200000]<int>(int *lhs, int *rhs)
{
  int temp; // [rsp+0h] [rbp-14h]

  temp = *lhs;
  *lhs = *rhs;
  *rhs = temp;
}