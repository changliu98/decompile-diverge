void __cdecl std::swap[abi:nn200000]<int>(int *pa, int *pb)
{
  int t; // [rsp+0h] [rbp-14h]

  t = *pa;
  *pa = *pb;
  *pb = t;
}