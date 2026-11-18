void __cdecl std::swap<int>(int *pfirstNumber, int *psecondNumber)
{
  int temp = *pfirstNumber;
  *pfirstNumber = *psecondNumber;
  *psecondNumber = temp;
}