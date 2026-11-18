// Swaps the values of two integers.
void __cdecl std::swap<int>(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}