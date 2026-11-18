double __cdecl calculate_product_over_size(int *numbers, int size)
{
  double product = 1.0;

  for (int i = 0; i < size; ++i)
  {
    product *= (double)numbers[i];
  }

  return product / (double)size;
}