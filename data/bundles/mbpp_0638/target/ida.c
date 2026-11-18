int __cdecl func0(int v, int t)
{
  double v2; // xmm0_8
  double v4; // [rsp+10h] [rbp-20h]

  v4 = pow((double)v, 0.16) * -11.37 + (double)t * 0.6215000000000001 + 13.12;
  v2 = pow((double)v, 0.16);
  return (int)round(0.3965 * (double)t * v2 + v4);
}