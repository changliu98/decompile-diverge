void set_word(void *addr, int val)
{
  int *word = (int *)addr;
  *word = val;
}