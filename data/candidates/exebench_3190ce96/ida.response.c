void __cdecl std::swap[abi:nn200000]<int>(int *p, int *q)
{
  int temp; // [rsp+0h] [rbp-14h]

  temp = *p;
  *p = *q;
  *q = temp;
}