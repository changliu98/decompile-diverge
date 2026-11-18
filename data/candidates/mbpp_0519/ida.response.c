double __cdecl func0(int num)
{
  double v1; // xmm0_8
  double v3; // [rsp+8h] [rbp-18h]

  v3 = pow((double)num, 3.0);
  v1 = sqrt(2.0);
  return round(100.0 * (v3 / (6.0 * v1))) / 100.0;
}