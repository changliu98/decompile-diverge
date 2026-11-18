void fn_5(double *a, double *b, double *sum, double *prod)
{
  int i;
  double *a_local = a;
  double *b_local = b;
  double *sum_local = sum;
  double *prod_local = prod;

  for (i = 0; i < 10; i++)
    sum_local[i] = a_local[i] * b_local[i];

  prod_local[i] = a_local[i] * b_local[i];
}