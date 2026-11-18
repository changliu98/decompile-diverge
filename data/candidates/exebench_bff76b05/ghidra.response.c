void project(int n,double *x,int *pivot)

{
  int i;
  int *pivot_local;
  double *x_local;
  int n_local;
  
  for (i = 0; i < n; i = i + 1) {
    if (pivot[i] != 0) {
      x[i] = 0.0;
    }
  }
  return;
}