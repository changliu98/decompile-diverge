void __cdecl std::swap[abi:nn200000]<int>(int *left, int *right)
{
  int tmp; // [rsp+0h] [rbp-14h]

  tmp = *left;
  *left = *right;
  *right = tmp;
}