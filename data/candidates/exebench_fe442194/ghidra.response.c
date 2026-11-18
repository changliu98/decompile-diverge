void inplace_swap(int *x,int *y)

{
  int *y_local;
  int *x_local;
  
  *y = *x ^ *y;
  *x = *x ^ *y;
  *y = *x ^ *y;
  return;
}