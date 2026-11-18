void DoAdjust(int *x,int *y,int dx,int dy,int cols,int rows)

{
  int rows_local;
  int cols_local;
  int dy_local;
  int dx_local;
  int *y_local;
  int *x_local;
  
  *x = *x + -1;
  *y = *y + -1;
  *x = dx + *x;
  if (*x < 0) {
    *x = cols - *x;
    *y = *y - *x / cols;
    *x = cols - *x % cols;
  }
  *y = *x / cols + *y;
  *x = *x % cols;
  *y = dy + *y;
  *x = *x + 1;
  *y = *y + 1;
  return;
}