int func0(int *array, int size)
{
  int gcd = find_gcd(array[0], array[1]);
  int i = 2;
  for (i = 2; i < size; i++)
    gcd = find_gcd(gcd, array[i]);
  return gcd;
}