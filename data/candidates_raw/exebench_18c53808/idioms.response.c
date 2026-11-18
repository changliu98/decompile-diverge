void adjust(struct _rect *dst, struct _rect *src)
{
  int x; int y; int w; int h;
  if (src == ((void *)0))
    return;
  if (dst->x > src->x)
    x = dst->x;
  else
    x = src->x;
  if (dst->y > src->y)
    y = dst->y;
  else
    y = src->y;
  if (dst->x + dst->w < src->x + src->w)
    w = dst->x + dst->w;
  else
    w = src->x + src->w;
  if (dst->y + dst->h < src->y + src->h)
    h = dst->y + dst->h;
  else
    h = src->y + src->h;
  dst->x = x;
  dst->y = y;
  dst->w = w - x;
  dst->h = h - y;
}