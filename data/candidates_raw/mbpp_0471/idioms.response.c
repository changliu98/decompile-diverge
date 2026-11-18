int mul(int *array, int length, int mod)
{
  int i;
  int result = 1;
  for (i = 0; i < length; i++)
    result = (array[i] % mod * result) % mod;
  return (result % mod);
}