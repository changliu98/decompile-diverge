void drv_generic_graphic_window(int pos, int size, int max, int *wpos, int *wsize)
{
 int p2 = pos + size;

 *wpos = 0;
 *wsize = 0;

 if (pos > max || p2 < 0 || size <= 0)
  return;

 if (pos < 0)
  pos = 0;

 if (p2 > max)
  p2 = max;

 *wpos = pos;
 *wsize = p2 - pos;
}