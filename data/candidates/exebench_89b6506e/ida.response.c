void __cdecl std::swap[abi:nn200000]<int>(int *num1, int *num2)
{
  int tmp; // [rsp+0h] [rbp-14h]

  tmp = *num1;
  *num1 = *num2;
  *num2 = tmp;
}