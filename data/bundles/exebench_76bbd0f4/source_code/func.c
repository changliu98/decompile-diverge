
void assignops(int *x, int y)
{
  *x >>= y;
  *x <<= y;
  *x += y;
  *x *= y;
  *x /= y;
  *x ^= y;
  *x -= y;
  *x &= y;
  *x |= y;
  *x %= y;
  *x = y;
}
