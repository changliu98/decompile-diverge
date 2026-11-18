void fb_hFixCoordsOrder(int *x1,int *y1,int *x2,int *y2)

{
  int *y2_local;
  int *x2_local;
  int *y1_local;
  int *x1_local;
  
  if (*x2 < *x1) {
    *x1 = *x2 ^ *x1;
    *x2 = *x1 ^ *x2;
    *x1 = *x2 ^ *x1;
  }
  if (*y2 < *y1) {
    *y1 = *y2 ^ *y1;
    *y2 = *y1 ^ *y2;
    *y1 = *y2 ^ *y1;
  }
  return;
}