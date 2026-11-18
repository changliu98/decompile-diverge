int func0(int *block, int size, int w)
{
  int sum = 0;
  int i;
  for (i = 0; i < size / 2; i++) {
    if (block[i] != block[size - 1 - i])
      return 0;
    sum += block[size - 1 - i] + block[i];
  }
  if (size % 2 == 1)
    sum += block[size / 2];
  if (sum > w)
    return 0;
  return 1;
}