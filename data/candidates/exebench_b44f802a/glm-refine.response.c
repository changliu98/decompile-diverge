void __cdecl YvVfilterCoef(double sigma, double *filter)
{
  // Precomputed constants
  const double m1 = 1.10783;
  const double m2 = 1.40586;
  const double m1sq = m1 * m1; // 1.22729
  const double m2sq = m2 * m2; // 1.97644
  const double a = 1.1668;
  
  double q, scale, q2;

  // Determine the parameter q based on the input sigma
  if (sigma >= 3.556)
    q = (sigma - 3.556) * 0.9804 + 2.5091;
  else
    q = 0.0561 * sigma * sigma + 0.5784 * sigma - 0.2568;

  q2 = q * q;
  
  // Calculate the normalization scale factor
  scale = (q + a) * (q2 + 2.0 * m1 * q + m1sq + m2sq);

  // Calculate the 7-tap symmetric filter coefficients
  filter[0] = q2 * q / scale;
  filter[1] = -q2 * (3.0 * q + 2.0 * m1 + a) / scale;
  filter[2] = -q * (3.0 * q2 + (2.0 * a + 4.0 * m1) * q + 2.0 * a * m1 + m1sq + m2sq) / scale;
  filter[3] = a * (m1sq + m2sq) / scale;
  filter[4] = filter[2];
  filter[5] = filter[1];
  filter[6] = filter[0];
}