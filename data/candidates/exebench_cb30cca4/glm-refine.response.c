void __cdecl std::swap<int>(int *pFirstNum, int *pSecondNum)
{
  int temp = *pFirstNum;
  *pFirstNum = *pSecondNum;
  *pSecondNum = temp;
}