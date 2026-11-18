void __cdecl std::swap[abi:nn200000]<int>(int *px, int *py)
{
  int temp; // [rsp+0h] [rbp-14h]

  temp = *px;
  *px = *py;
  *py = temp;
}