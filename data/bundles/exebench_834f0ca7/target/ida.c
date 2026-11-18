void __cdecl FindDivDiff5Coeff1(double a, double b, double c, double *dd)
{
  double cb; // [rsp+0h] [rbp-38h]
  double ca; // [rsp+8h] [rbp-30h]
  double ba; // [rsp+10h] [rbp-28h]

  ba = 1.0 / (b - a);
  ca = 1.0 / (c - a);
  cb = 1.0 / (c - b);
  dd[1] = ba * ba * ca * ca;
  *dd = 2.0 * (ca + ba) * dd[1];
  dd[3] = cb * cb * ba * ba;
  dd[2] = 2.0 * (cb - ba) * dd[3];
  dd[5] = cb * cb * ca * ca;
  dd[4] = -2.0 * (cb + ca) * dd[5];
}