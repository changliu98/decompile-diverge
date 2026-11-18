int putdword(void *ptr, int val)
{
  int *p = (int *)ptr;
  *p = (val);
  return (val);
}