static void shr(struct u128 *r, int n)
{
  if (n >= 64)
  {
    n -= 64;
    r->hi = r->lo;
    r->lo = 0;
  }
  r->hi = r->hi << n | r->lo >> (64 - n);
  r->lo = r->lo << n;
}