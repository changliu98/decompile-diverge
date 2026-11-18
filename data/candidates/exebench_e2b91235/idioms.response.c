int num_to_array(int *array, int num)
{
  int i = 0;
  while (num > 0)
  {
    array[i++] = num % 10;
    num /= 10;
  }
  return i;
}