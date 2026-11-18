void _vector_swap(void *a, void *b)
{
  void *tmp;
  tmp = a;
  a = b;
  b = tmp;
}