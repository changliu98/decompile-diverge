void setSizes(int m, int n, int *Q_size, int *R_size, int *permSize){
  Q_size[1] = m;
  Q_size[0] = m;
  *permSize = n;
  R_size[0] = m;
  R_size[1] = n;
}