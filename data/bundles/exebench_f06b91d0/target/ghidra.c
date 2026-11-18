void add_vector(double *a,double *b,double *out)

{
  int i;
  double *out_local;
  double *b_local;
  double *a_local;
  
  for (i = 0; i < 3; i = i + 1) {
    out[i] = a[i] + b[i];
  }
  return;
}