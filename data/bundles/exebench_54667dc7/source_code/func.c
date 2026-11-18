







static void drv_generic_graphic_window(int pos, int size, int max, int *wpos, int *wsize)
{
    int p1 = pos;
    int p2 = pos + size;

    *wpos = 0;
    *wsize = 0;

    if (p1 > max || p2 < 0 || size < 1)
 return;

    if (p1 < 0)
 p1 = 0;

    if (p2 > max)
 p2 = max;

    *wpos = p1;
    *wsize = p2 - p1;
}
