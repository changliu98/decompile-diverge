int __cdecl func0(int n)
{
  double v1; // xmm0_8
  double x; // [rsp+0h] [rbp-10h]

  v1 = pow(10.0, (double)(n - 1));
  x = sqrt(2.0 * v1);
  return (int)round(x);
}