xadUINT32 xdl_bogosqrt(xadUINT32 n)
{
  xadUINT32 i = 1;

  while(n > 0)
  {
    i <<= 1;
    n >>= 2;
  }

  return i;
}