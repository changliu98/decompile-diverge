void __cdecl std::swap[abi:nn200000]<int>(int *i, int *j)
{
  int temp = *i;
  *i = *j;
  *j = temp;
}