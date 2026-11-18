void drv_generic_graphic_window(int pos,int size,int max,int *wpos,int *wsize)

{
  int p2;
  int p1;
  int *wsize_local;
  int *wpos_local;
  int max_local;
  int size_local;
  int pos_local;
  
  p2 = pos + size;
  *wpos = 0;
  *wsize = 0;
  if (((pos <= max) && (-1 < p2)) && (0 < size)) {
    p1 = pos;
    if (pos < 0) {
      p1 = 0;
    }
    if (max < p2) {
      p2 = max;
    }
    *wpos = p1;
    *wsize = p2 - p1;
  }
  return;
}