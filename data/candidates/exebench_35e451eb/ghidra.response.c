void adjust_point(int *n)

{
  int *n_local;
  
  if (*n < 0) {
    *n = 0;
  }
  else if (100 < *n) {
    *n = 100;
  }
  return;
}