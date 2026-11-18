int __cdecl func0(int v, int t)
{
  double v_pow = pow((double)v, 0.16);
  double v4 = v_pow * -11.37 + (double)t * 0.6215000000000001 + 13.12;
  return (int)round(0.3965 * (double)t * v_pow + v4);
}