unsigned __int64 __cdecl xorshf96(unsigned __int64 *x, unsigned __int64 *y, unsigned __int64 *z)
{
  unsigned __int64 t; // [rsp+0h] [rbp-20h]

  *x ^= *x << 16;
  *x ^= *x >> 5;
  *x ^= 2 * *x;
  t = *x;
  *x = *y;
  *y = *z;
  *z = *y ^ *x ^ t;
  return *z;
}