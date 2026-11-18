void __cdecl multiplyByConstant(int (*src)[3], int multiplier)
{
  int *matrix = (int *)src;
  
  for (int i = 0; i < 9; ++i)
  {
    matrix[i] *= multiplier;
  }
}