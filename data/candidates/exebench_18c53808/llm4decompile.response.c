void gui_combine_scissor(struct gui_scissor *dst, struct gui_scissor *src)
{
 if (!src)
  return;

 int x1 = src->x;
 int y1 = src->y;
 int x2 = src->x + src->w;
 int y2 = src->y + src->h;

 if (x1 < dst->x)
  x1 = dst->x;
 if (y1 < dst->y)
  y1 = dst->y;
 if (x2 > dst->x + dst->w)
  x2 = dst->x + dst->w;
 if (y2 > dst->y + dst->h)
  y2 = dst->y + dst->h;

 dst->x = x1;
 dst->y = y1;
 dst->w = x2 - x1;
 dst->h = y2 - y1;
}