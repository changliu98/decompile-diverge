void __cdecl std::swap[abi:nn200000]<int>(int *pa, int *pb)
{
  int tmp; // [rsp+0h] [rbp-14h]

  tmp = *pa;
  *pa = *pb;
  *pb = tmp;
}