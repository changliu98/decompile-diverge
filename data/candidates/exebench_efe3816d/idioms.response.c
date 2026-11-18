int metric(double *x, double *y, double *z, double *id)
{
  int i;
  for (i = 0; i < 9; i++)
    id[i] = 0.;
  id[8] = 1.;
  id[4] = 1.;
  id[0] = 1.;
  return 0;
}