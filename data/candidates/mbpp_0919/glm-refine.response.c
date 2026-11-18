int __cdecl func0(int *items, int length)
{
  int product = 1;
  for (int i = 0; i < length; ++i)
    product *= items[i];
  return product;
}