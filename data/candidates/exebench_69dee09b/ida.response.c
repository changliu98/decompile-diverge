void __cdecl std::swap[abi:nn200000]<int>(int *i, int *j)
{
  int temp; // [rsp+0h] [rbp-14h]

  temp = *i;
  *i = *j;
  *j = temp;
}