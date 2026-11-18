void __cdecl std::swap[abi:nn200000]<int>(int *a, int *b)
{
  int tmp; // [rsp+0h] [rbp-14h]

  tmp = *a;
  *a = *b;
  *b = tmp;
}