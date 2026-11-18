int64_t __cdecl search(
        const int64_t *I,
        const uint8_t *old,
        int64_t oldsize,
        const uint8_t *a4,
        int64_t newsize,
        int64_t st,
        int64_t en,
        int64_t *pos)
{
  int v8; // eax
  const uint8_t *s1; // [rsp+28h] [rbp-58h]
  int64_t y; // [rsp+38h] [rbp-48h]
  int64_t x; // [rsp+40h] [rbp-40h]
  int64_t xa; // [rsp+40h] [rbp-40h]

  if ( en - st >= 2 )
  {
    xa = (en - st) / 2 + st;
    s1 = &old[I[xa]];
    if ( oldsize - I[xa] >= newsize )
      v8 = memcmp(s1, a4, newsize);
    else
      v8 = memcmp(s1, a4, oldsize - I[xa]);
    if ( v8 >= 0 )
      return search(I, old, oldsize, a4, newsize, st, xa, pos);
    else
      return search(I, old, oldsize, a4, newsize, xa, en, pos);
  }
  else
  {
    x = matchlen(&old[I[st]], oldsize - I[st], a4, newsize);
    y = matchlen(&old[I[en]], oldsize - I[en], a4, newsize);
    if ( x <= y )
    {
      *pos = I[en];
      return y;
    }
    else
    {
      *pos = I[st];
      return x;
    }
  }
}