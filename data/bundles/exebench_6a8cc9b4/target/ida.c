void __cdecl std::swap[abi:nn200000]<int>(int *k, int *m)
{
  int s; // [rsp+0h] [rbp-14h]

  s = *k;
  *k = *m;
  *m = s;
}