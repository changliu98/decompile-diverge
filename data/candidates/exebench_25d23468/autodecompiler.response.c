void shr(struct bitbuf *b, int n)
{
 if ((unsigned)n >= sizeof(b->hi) * 8) {
  n -= sizeof(b->hi) * 8;
  b->lo = b->hi;
  b->hi = 0;
 }
 b->lo >>= n;
 b->lo |= b->hi << (sizeof(b->hi) * 8 - n);
 b->hi >>= n;
}