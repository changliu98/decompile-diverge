void long_swap(void *a, void *b)
{
  void *tmp = a;
  a = b;
  b = tmp;
}