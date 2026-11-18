void __cdecl std::swap[abi:nn200000]<int>(int *a, int *b)
{
  int box; // [rsp+0h] [rbp-14h]

  box = *a;
  *a = *b;
  *b = box;
}