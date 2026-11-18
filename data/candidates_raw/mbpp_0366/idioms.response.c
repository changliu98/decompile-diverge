int find_max_product(int *list, unsigned long list_length)
{
  int max_product = list[0] * list[1];
  unsigned long i = 1;
  for (i = 1; i < list_length - 1; i++)
  {
    if (list[i] * list[i + 1] > max_product)
    {
      max_product = list[i] * list[i + 1];
    }
  }
  return max_product;
}