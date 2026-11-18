// Swaps the values of two integers.
void __cdecl std::swap<int>(int *num1, int *num2)
{
  int temp = *num1;
  *num1 = *num2;
  *num2 = temp;
}