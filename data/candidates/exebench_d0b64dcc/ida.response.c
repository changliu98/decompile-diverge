void __cdecl std::swap[abi:nn200000]<int>(int *p, int *q)
{
  int tmp; // [rsp+0h] [rbp-14h]

  tmp = *p;
  *p = *q;
  *q = tmp;
}