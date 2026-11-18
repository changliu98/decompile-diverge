int
fetch_and_add (long long unsigned int *ptr, long long unsigned int val)
{
  return __atomic_fetch_add_8 (ptr, val, 5);
}