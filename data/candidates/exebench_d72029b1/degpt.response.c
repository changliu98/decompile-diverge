void test1(short n,int *x)

{
  short i;
  int *x_local;
  short n_local;
  
  for (i = 0; i < n; i = i + 2) {
    x[(short)(i + 1)] = 0;
  }
  return;
}