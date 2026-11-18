long __cdecl incr(long *p, long val)
{
  long old_val = *p;
  *p += val;
  return old_val;
}