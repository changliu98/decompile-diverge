void __swap(void *a, void *b)
{
  void *tmp;
  tmp = a;
  a = b;
  b = tmp;
}