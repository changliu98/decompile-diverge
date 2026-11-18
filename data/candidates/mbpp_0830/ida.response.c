double __cdecl func0(double a, int digits)
{
  double v2; // xmm0_8
  double v4; // [rsp+8h] [rbp-28h]
  double v5; // [rsp+10h] [rbp-20h]
  double n; // [rsp+18h] [rbp-18h]

  n = pow(10.0, (double)-digits);
  v4 = ceil(a / n) * n;
  v2 = pow(10.0, (double)digits);
  v5 = round(v4 * v2);
  return v5 / pow(10.0, (double)digits);
}