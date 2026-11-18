void __cdecl std::swap[abi:nn200000]<int>(int *left, int *right)
{
  int temp; // [rsp+0h] [rbp-14h]

  temp = *left;
  *left = *right;
  *right = temp;
}