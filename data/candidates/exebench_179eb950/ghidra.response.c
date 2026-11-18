void swap_int(int *x,int *y)

{
  int *y_local;
  int *x_local;
  
  *y = *x ^ *y;
  *x = *y ^ *x;
  *y = *x ^ *y;
  return;
}