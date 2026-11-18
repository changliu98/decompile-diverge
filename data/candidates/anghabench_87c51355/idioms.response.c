int spc_used(void *head, void *tail, int size)
{
  int diff = (int)head - (int)tail;
  if (diff >= 0)
    return diff;
  return diff + size;
}