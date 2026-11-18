int clip_img(int clip_x1,int clip_y1,int clip_x2,int clip_y2,int *x,int *y,int *w,int *h,int *sx,
            int *sy,int mx,int my)

{
  undefined1 local_29;
  int *y_local;
  int *x_local;
  int clip_y2_local;
  int clip_x2_local;
  int clip_y1_local;
  int clip_x1_local;
  
  if (*x < clip_x1) {
    *w = *w - (clip_x1 - *x);
    *sx = (clip_x1 - *x) * mx + *sx;
    *x = clip_x1;
  }
  if ((clip_x2 - *x) + 1 < *w) {
    *w = (clip_x2 - *x) + 1;
  }
  if (*y < clip_y1) {
    *h = *h - (clip_y1 - *y);
    *sy = (clip_y1 - *y) * my + *sy;
    *y = clip_y1;
  }
  if ((clip_y2 - *y) + 1 < *h) {
    *h = (clip_y2 - *y) + 1;
  }
  local_29 = false;
  if (-1 < *w) {
    local_29 = -1 < *h;
  }
  return (int)local_29;
}