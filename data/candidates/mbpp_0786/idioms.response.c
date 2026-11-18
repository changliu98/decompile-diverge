int func0(int *array, int n, int x)
{
  int i = 0;
  for (i = 0; i < n && array[i] <= x; i++)
    ;
  return i;
}