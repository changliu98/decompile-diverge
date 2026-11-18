float KBND_REPLICATE(float *img,int w,int h,int x,int y,float bnd_const)

{
  float bnd_const_local;
  int y_local;
  int x_local;
  int h_local;
  int w_local;
  float *img_local;
  
  x_local = x;
  if (x < 0) {
    x_local = 0;
  }
  if (w <= x_local) {
    x_local = w + -1;
  }
  y_local = y;
  if (y < 0) {
    y_local = 0;
  }
  if (h <= y_local) {
    y_local = h + -1;
  }
  return img[y_local * w + x_local];
}