void __cdecl std::swap[abi:nn200000]<int>(int *const p1, int *const p2)
{
  int tmp; // [rsp+0h] [rbp-14h]

  tmp = *p1;
  *p1 = *p2;
  *p2 = tmp;
}