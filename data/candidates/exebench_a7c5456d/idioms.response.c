static inline int *atomic_fetch_add(int *var, int offset)
{
  int ret = *var;
  *var += offset;
  return (int *)ret;
}