static inline int *int_offset(int *var, int offset)
{
  int ret = *var;
  *var += offset;
  return (int *)ret;
}