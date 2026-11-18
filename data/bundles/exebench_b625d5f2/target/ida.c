void __cdecl compute_matrix_T(double *T, double a, double b, double c, double d)
{
  *T = a;
  T[1] = a * b;
  T[2] = 3.0 * a * d;
  T[3] = a * (3.0 * b * d + a * c);
}