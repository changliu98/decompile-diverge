void __cdecl std::swap[abi:nn200000]<int>(int *item1, int *item2)
{
  int tmp; // [rsp+0h] [rbp-14h]

  tmp = *item1;
  *item1 = *item2;
  *item2 = tmp;
}