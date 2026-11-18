int __cdecl clip_img(
        int clip_x1,
        int clip_y1,
        int clip_x2,
        int clip_y2,
        int *x,
        int *y,
        int *w,
        int *h,
        int *sx,
        int *sy,
        int mx,
        int my)
{
  bool v13; // [rsp+1h] [rbp-21h]

  if ( *x < clip_x1 )
  {
    *w -= clip_x1 - *x;
    *sx += mx * (clip_x1 - *x);
    *x = clip_x1;
  }
  if ( *w > clip_x2 - *x + 1 )
    *w = clip_x2 - *x + 1;
  if ( *y < clip_y1 )
  {
    *h -= clip_y1 - *y;
    *sy += my * (clip_y1 - *y);
    *y = clip_y1;
  }
  if ( *h > clip_y2 - *y + 1 )
    *h = clip_y2 - *y + 1;
  v13 = 0;
  if ( *w >= 0 )
    return *h >= 0;
  return v13;
}