int
a_fetch_add (int *ptr, int val)
{
  return __atomic_fetch_add_4 (ptr, val, 5);
}