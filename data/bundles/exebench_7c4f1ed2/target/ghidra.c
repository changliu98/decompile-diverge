void decode_dir(short d,int *x,int *y)

{
  int *y_local;
  int *x_local;
  short d_local;
  
  *x = ((int)d & 0xffU) - 2;
  *y = ((int)((int)d & 0xff00U) >> 8) + -2;
  return;
}