void __cdecl FindDivDiff5Coeff1(double a, double b, double c, double *dd)
{
  // Precompute the reciprocals of the differences between the points.
  // These represent the denominators of the first-order divided differences.
  double inv_ba = 1.0 / (b - a);
  double inv_ca = 1.0 / (c - a);
  double inv_cb = 1.0 / (c - b);

  // Compute the squared terms to avoid redundant multiplications later.
  double inv_ba_sq = inv_ba * inv_ba;
  double inv_ca_sq = inv_ca * inv_ca;
  double inv_cb_sq = inv_cb * inv_cb;

  // Calculate the coefficients and store them in the output array `dd`.
  // The pattern follows the structure of second-order divided differences 
  // or coefficients of a polynomial interpolant (e.g., Lagrange basis derivatives).
  
  // dd[0] and dd[1] relate to the interval [a, b] and point c
  dd[1] = inv_ba_sq * inv_ca_sq;
  *dd   = 2.0 * (inv_ca + inv_ba) * dd[1];

  // dd[2] and dd[3] relate to the interval [b, c] and point a
  dd[3] = inv_cb_sq * inv_ba_sq;
  dd[2] = 2.0 * (inv_cb - inv_ba) * dd[3];

  // dd[4] and dd[5] relate to the interval [c, a] and point b
  dd[5] = inv_cb_sq * inv_ca_sq;
  dd[4] = -2.0 * (inv_cb + inv_ca) * dd[5];
}