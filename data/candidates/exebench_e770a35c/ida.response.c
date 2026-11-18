void __cdecl std::swap[abi:nn200000]<int>(int *i1, int *i2)
{
  int temp; // [rsp+0h] [rbp-14h]

  temp = *i1;
  *i1 = *i2;
  *i2 = temp;
}