void swap_l(void *a, void *b)
{
  void *tmp;
  tmp = a;
  a = b;
  b = tmp;
}