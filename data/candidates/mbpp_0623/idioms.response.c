void func0(int *array, int length, int n, int *result)
{
  int i;
  for (i = 0; i < length; i++)
    result[i] = pow(array[i], n);
}