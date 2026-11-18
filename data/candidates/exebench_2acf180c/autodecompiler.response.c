void unpackFloat(float f, int *e, unsigned long *m)
{
 union { float f; unsigned long l; } u;
 u.f = f;
 *e = ((u.l & 0x7f800000) >> 23) - 127;
 *m = (u.l & 0x7fffff) + 0x800000;
 if (u.l & 0x80000000)
  *m = 0 - *m;
}