void foo(int *x,int *y)

{
  int i;
  int *y_local;
  int *x_local;
  
  for (i = 0; (i < 8 && (y[i] == i + 2)); i = i + 1) {
  }
  if ((i == 8) && (*x == 1)) {
    *x = 8;
    for (i = 0; i < 8; i = i + 1) {
      y[i] = i + 9;
    }
  }
  else {
    *x = 6;
  }
  return;
}