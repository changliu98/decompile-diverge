void __cdecl std::swap[abi:nn200000]<int>(int *a, int *b)
{
  int num; // [rsp+0h] [rbp-14h]

  num = *a;
  *a = *b;
  *b = num;
}