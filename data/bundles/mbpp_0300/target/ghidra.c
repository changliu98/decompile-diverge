double func0(int n)

{
  int r;
  double res;
  double nCr;
  int n_local;
  
  nCr = DAT_00102008;
  res = DAT_00102008;
  for (r = 1; r <= n; r = r + 1) {
    nCr = (nCr * (double)((n + 1) - r)) / (double)r;
    res = nCr * nCr + res;
  }
  return res;
}