int product(int *items, int length)
{
  int i;
  int total = 1;
  for (i = 0; i < length; i++)
    total *= items[i];
  return total;
}