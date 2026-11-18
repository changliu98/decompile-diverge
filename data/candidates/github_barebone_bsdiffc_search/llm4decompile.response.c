int64_t search(int64_t *I, unsigned char *old, int64_t oldsize, unsigned char *new, int64_t newsize, int64_t st, int64_t en, int64_t *pos)
{
  int64_t x, y;

  if (en - st < 2) {
    x = matchlen(old + I[st], oldsize - I[st], new, newsize);
    y = matchlen(old + I[en], oldsize - I[en], new, newsize);

    if (x > y) {
      *pos = I[st];
      return x;
    } else {
      *pos = I[en];
      return y;
    }
  }

  int64_t half = (en - st) / 2;
  int64_t one = newsize;
  int64_t two = oldsize - I[st + half];

  if (one > two) one = two;
  int64_t cmp = memcmp(old + I[st + half], new, one);

  if (cmp >= 0) {
    return search(I, old, oldsize, new, newsize, st, st + half, pos);
  } else {
    return search(I, old, oldsize, new, newsize, st + half, en, pos);
  }
}