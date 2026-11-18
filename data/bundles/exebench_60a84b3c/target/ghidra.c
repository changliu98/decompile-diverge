char sraClipRect2(int *x,int *y,int *x2,int *y2,int cx,int cy,int cx2,int cy2)

{
  undefined1 local_31;
  int cy_local;
  int cx_local;
  int *y2_local;
  int *x2_local;
  int *y_local;
  int *x_local;
  
  if (*x < cx) {
    *x = cx;
  }
  if (*y < cy) {
    *y = cy;
  }
  if (cx2 <= *x) {
    *x = cx2 + -1;
  }
  if (cy2 <= *y) {
    *y = cy2 + -1;
  }
  if (*x2 <= cx) {
    *x2 = cx + 1;
  }
  if (*y2 <= cy) {
    *y2 = cy + 1;
  }
  if (cx2 < *x2) {
    *x2 = cx2;
  }
  if (cy2 < *y2) {
    *y2 = cy2;
  }
  local_31 = false;
  if (*x < *x2) {
    local_31 = *y < *y2;
  }
  return local_31;
}