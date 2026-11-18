void h(int *x,int y)

{
  int y_local;
  int *x_local;
  
  if (y < *x) {
    h(x,*x);
  }
  else {
    *x = *x - y;
  }
  return;
}