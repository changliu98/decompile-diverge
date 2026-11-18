void __cdecl std::swap[abi:nn200000]<int>(int *const pint1, int *const pint2)
{
  int temp; // [rsp+0h] [rbp-14h]

  temp = *pint1;
  *pint1 = *pint2;
  *pint2 = temp;
}