long __cdecl incr(long *p, long val)
{
  long x; // [rsp+8h] [rbp-18h]

  x = *p;
  *p += val;
  return x;
}