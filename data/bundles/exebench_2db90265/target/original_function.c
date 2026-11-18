int inicializa(int *vec, int n, int *min, int *max) {
  int i = 0;
  if (n % 2 != 0) {
    *min = vec[0];
    *max = vec[0];
    i = 1;
  }
  else {
    i = 2;
    if (vec[0] < vec[1]) {
      *min = vec[0];
      *max = vec[1];
    }
    else {
      *min = vec[1];
      *max = vec[0];
    }
  }
  return i;
}