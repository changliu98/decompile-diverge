void __cdecl std::swap[abi:nn200000]<int>(int *num1, int *num2)
{
  int temp; // [rsp+0h] [rbp-14h]

  temp = *num1;
  *num1 = *num2;
  *num2 = temp;
}