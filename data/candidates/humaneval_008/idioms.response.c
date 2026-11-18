void func0(int *numbers, int size, int *result)
{
  int sum = 0;
  int product = 1;
  int i = 0;
  for (i = 0; i < size; i++)
  {
    sum += numbers[i];
    product *= numbers[i];
  }
  result[0] = sum;
  result[1] = product;
}