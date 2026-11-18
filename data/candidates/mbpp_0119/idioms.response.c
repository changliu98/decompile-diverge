int func0(int *array, int n)
{
  int i; int xor = 0;
  for (i = 0; i < n; i++)
    xor = xor ^ array[i];
  return (xor);
}