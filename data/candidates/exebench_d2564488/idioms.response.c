void multiplyByConstant(int (*m)[3], int factor)
{
  int i; int j;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      (*m)[i * 3 + j] *= factor;
}