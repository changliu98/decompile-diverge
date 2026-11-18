void __cdecl std::swap[abi:nn200000]<int>(int *pFirstNum, int *pSecondNum)
{
  int temp; // [rsp+0h] [rbp-14h]

  temp = *pFirstNum;
  *pFirstNum = *pSecondNum;
  *pSecondNum = temp;
}