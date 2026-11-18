void __cdecl compute_matrix_T(double *T, double a, double b, double c, double d)
{
  // Precompute common sub-expressions to clarify the underlying polynomial structure
  double a_sq = a * a;
  double bd  = b * d;

  // T[0] = a
  *T       = a;
  
  // T[1] = a * b
  T[1]     = a * b;
  
  // T[2] = 3 * a * d
  T[2]     = 3.0 * a * d;
  
  // T[3] = 3 * a * b * d + a^2 * c
  T[3]     = a * (3.0 * bd + a_sq * c);
}