void __cdecl calculate_sum_and_product(const int *numbers, int size, int *result)
{
  int sum = 0;
  int product = 1;

  for (int i = 0; i < size; ++i)
  {
    sum += numbers[i];
    product *= numbers[i];
  }

  // Store the sum and product in the result array
  result[0] = sum;
  result[1] = product;
}