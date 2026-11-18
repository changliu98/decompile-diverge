void add_a_vector(double c, int n, double *x, double *y)
{
  do {
    *y++ += c * *x++;
  } while (--n);
}