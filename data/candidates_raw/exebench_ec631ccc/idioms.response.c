void project_to_box(double *lamda, double *x, double *h, double *boxlo)
{
  x[0] = boxlo[0] + lamda[0]*h[0] + lamda[1]*h[5] + lamda[2]*h[4];
  x[1] = boxlo[1] + lamda[1]*h[1] + lamda[2]*h[3];
  x[2] = boxlo[2] + lamda[2]*h[2];
  return;
}