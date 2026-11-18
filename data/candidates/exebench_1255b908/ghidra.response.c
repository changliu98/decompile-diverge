int clip_wh(int *x,int *width,int min_width,int max_width)

{
  int xoff;
  int max_width_local;
  int min_width_local;
  int *width_local;
  int *x_local;
  undefined4 local_c;
  
  if (*x < min_width) {
    local_c = min_width - *x;
    *width = *x + *width;
    *x = min_width;
  }
  else {
    if (max_width <= *x + *width) {
      *width = max_width - *x;
    }
    local_c = 0;
  }
  return local_c;
}