void __cdecl std::swap[abi:nn200000]<int>(int *a, int *b)
{
  int temp; // [rsp+0h] [rbp-14h]

  temp = *a;
  *a = *b;
  *b = temp;
}