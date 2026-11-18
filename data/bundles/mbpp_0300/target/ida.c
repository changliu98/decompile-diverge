double __cdecl func0(int n)
{
  int r; // [rsp+0h] [rbp-1Ch]
  double res; // [rsp+4h] [rbp-18h]
  double nCr; // [rsp+Ch] [rbp-10h]

  nCr = 1.0;
  res = 1.0;
  for ( r = 1; r <= n; ++r )
  {
    nCr = nCr * (double)(n + 1 - r) / (double)r;
    res = nCr * nCr + res;
  }
  return res;
}