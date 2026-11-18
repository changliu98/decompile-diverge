static int64_t search(int64_t *I, unsigned char *old, int64_t oldsize, unsigned char *new, int64_t newsize, int64_t st, int64_t en, int64_t *pos)
{
  int64_t x; int64_t y;
  if (en - st < 2)
  {
    x = matchlen(old + I[st], oldsize - I[st], new, newsize);
    y = matchlen(old + I[en], oldsize - I[en], new, newsize);
    if (x > y)
    {
      *pos = I[st];
      return x;
    }
    else
    {
      *pos = I[en];
      return y;
    }
  }
  int64_t mid = (en - st)/2 + st;
  unsigned char *midp = old + I[mid];
  int cmp = (oldsize - I[mid]) < newsize ?
    memcmp(midp, new, oldsize - I[mid]) :
    memcmp(midp, new, newsize);
  if (cmp < 0)
    return search(I, old, oldsize, new, newsize, mid, en, pos);
  else
    return search(I, old, oldsize, new, newsize, st, mid, pos);
}