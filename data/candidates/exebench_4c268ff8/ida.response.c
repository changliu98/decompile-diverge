void __cdecl std::swap[abi:nn200000]<int>(int *n, int *m)
{
  int temp; // [rsp+0h] [rbp-14h]

  temp = *n;
  *n = *m;
  *m = temp;
}