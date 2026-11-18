void wordstore(void *addr, int val)
{
  int *word = (int *)addr;
  *word = val;
}