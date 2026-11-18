void __cdecl std::swap[abi:nn200000]<int>(int *a, int *b)
{
  int buf; // [rsp+0h] [rbp-14h]

  buf = *a;
  *a = *b;
  *b = buf;
}