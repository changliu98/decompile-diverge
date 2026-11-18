int a_swap(int *ptr, int new)
{
  int prev;
  do {
    prev = *ptr;
    LOCK();
    if (*ptr == prev) *ptr = new;
    UNLOCK();
  } while (*ptr != prev);
  return prev;
}