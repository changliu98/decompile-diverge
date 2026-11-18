int __cdecl func0(int N)
{
  double v1; // xmm0_8
  double v2; // xmm0_8

  v1 = sqrt((double)N);
  v2 = floor(v1);
  return ((int)v2 + 1) * ((int)v2 + 1);
}