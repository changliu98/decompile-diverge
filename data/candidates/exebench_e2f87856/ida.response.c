void __cdecl std::swap[abi:nn200000]<int>(int *pfirstNumber, int *psecondNumber)
{
  int temp; // [rsp+0h] [rbp-14h]

  temp = *pfirstNumber;
  *pfirstNumber = *psecondNumber;
  *psecondNumber = temp;
}