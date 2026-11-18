void __cdecl drv_generic_graphic_window(int pos, int size, int max, int *wpos, int *wsize)
{
  int p2; // [rsp+0h] [rbp-28h]
  int p1; // [rsp+4h] [rbp-24h]

  p1 = pos;
  p2 = size + pos;
  *wpos = 0;
  *wsize = 0;
  if ( pos <= max && p2 >= 0 && size >= 1 )
  {
    if ( pos < 0 )
      p1 = 0;
    if ( p2 > max )
      p2 = max;
    *wpos = p1;
    *wsize = p2 - p1;
  }
}