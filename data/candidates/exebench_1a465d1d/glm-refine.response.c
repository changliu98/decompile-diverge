void __cdecl FindDivDiff5Coeff2(double a, double b, double c, double d, double *coeffs)
{
  double inv_ba = 1.0 / (b - a);
  double inv_ca = 1.0 / (c - a);
  double inv_cb = 1.0 / (c - b);
  double inv_da = 1.0 / (d - a);
  double inv_db = 1.0 / (d - b);
  double inv_dc = 1.0 / (d - c);

  coeffs[0] = -pow(inv_ba, 2) * pow(inv_ca, 2) * inv_da;
  coeffs[1] = -(inv_cb + inv_cb + inv_db - inv_ba) * inv_ba * inv_db * pow(inv_cb, 2);
  coeffs[2] = -inv_ba * inv_db * pow(inv_cb, 2);
  coeffs[3] = -(inv_dc - inv_cb - inv_cb - inv_ca) * inv_dc * inv_ca * pow(inv_cb, 2);
  coeffs[4] = -inv_dc * inv_ca * pow(inv_cb, 2);
  coeffs[5] = inv_da * pow(inv_db, 2) * pow(inv_dc, 2);
}