int func0(int *array, int n)
{
  int odd = 0;
  int i;
  for (i = 0; i < n; i++)
    if (array[i] % 2 == 1)
      odd++;
  if (odd % 2 == 0)
    return 2;
  else
    return 1;
}