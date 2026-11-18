void hil_s_from_xy(unsigned int x, unsigned int y, int order, unsigned int *s)
{
  int i;
  unsigned int state = 0;
  for (i = order - 1; i >= 0; i--)
  {
    *s = (*s << 2) | ((y >> i & 1) | (x >> i & 1) | (state << 2))
      & 3;
    state = ((y >> i & 1) | (x >> i & 1) | (state << 2))
      & 3;
  }
}