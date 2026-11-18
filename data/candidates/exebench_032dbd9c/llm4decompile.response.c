void poly_mul1(double *p1, double *p2, int d1, int d2, double *p3, int *d3)
{
 int i, j;
 *d3 = d1 + d2;
 for (i = 0; i < 17; i++)
  p3[i] = 0.0;
 for (i = 0; i <= d1; i++)
  for (j = 0; j <= d2; j++)
   p3[i + j] += p1[i] * p2[j];
}