void decode6(long v,long width,long height,long *x,long *y)

{
  long lVar1;
  long maxcol;
  long col;
  long D;
  long w;
  long *y_local;
  long *x_local;
  long height_local;
  long width_local;
  long v_local;
  
  D = 6;
  col = v / (height * 6);
  lVar1 = (width + -4) / 6;
  if (lVar1 <= col) {
    D = width + lVar1 * -6;
    col = lVar1;
  }
  lVar1 = v + col * height * -6;
  *x = col * 6 + lVar1 % D;
  *y = (height + -1) - lVar1 / D;
  return;
}