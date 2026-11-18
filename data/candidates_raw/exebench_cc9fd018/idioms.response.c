int add_size(void *a, void *b, void *res)
{
  void *tmp;
  unsigned long a_ = (size_t) a;
  unsigned long b_ = (size_t) b;
  if (res)
    tmp = res;
  else
    tmp = &tmp;
  *(unsigned long *)tmp = a_ + b_;
  if (tmp == (void *) (unsigned long) a_)
    return 0;
  return 1;
}