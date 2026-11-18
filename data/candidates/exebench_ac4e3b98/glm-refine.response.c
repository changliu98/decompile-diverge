void __cdecl swap_uint(unsigned int *p, unsigned int *q)
{
  unsigned int tmp = *p;
  *p = *q;
  *q = tmp;
}