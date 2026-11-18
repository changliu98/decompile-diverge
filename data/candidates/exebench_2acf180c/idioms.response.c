void unpackFloat(float f, int *exp, int *man)
{
  int i = (int)f;
  *exp = ((i & 0x7f800000) >> 23) - 127;
  *man = (i & 0x007fffff) + 0x800000;
  if (f < 0.0f)
    *man = -*man;
}