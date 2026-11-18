define MAX_POLY_COEFFS 17

void __cdecl poly_mul1(double *poly1, double *poly2, int deg1, int deg2, double *out_poly, int *out_deg)
{
  int i, j;

  // The degree of the product of two polynomials is the sum of their degrees
  *out_deg = deg1 + deg2;

  // Initialize the output polynomial coefficients to 0
  for (i = 0; i < MAX_POLY_COEFFS; ++i)
    out_poly[i] = 0.0;

  // Perform polynomial multiplication (convolution)
  for (i = 0; i <= deg1; ++i)
  {
    for (j = 0; j <= deg2; ++j)
    {
      out_poly[i + j] += poly1[i] * poly2[j];
    }
  }
}