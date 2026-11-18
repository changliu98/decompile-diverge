int inicializa(int *vec,int n,int *min,int *max)

{
  int i;
  int *max_local;
  int *min_local;
  int n_local;
  int *vec_local;
  
  if (n % 2 == 0) {
    i = 2;
    if (*vec < vec[1]) {
      *min = *vec;
      *max = vec[1];
    }
    else {
      *min = vec[1];
      *max = *vec;
    }
  }
  else {
    *min = *vec;
    *max = *vec;
    i = 1;
  }
  return i;
}