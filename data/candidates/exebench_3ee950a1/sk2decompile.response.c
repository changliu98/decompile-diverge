float hpluck(float input, float *par) {
  int i;
  float tmp, tmp2;
  par[0] += 1.0;
  if (par[1] < par[0]) par[0] = 20.0;
  i = (int)par[0];
  par[7] = par[i] * (1.0 - par[8]) + par[7] * par[8];
  tmp = par[2] * par[i] + par[3] * par[6];
  tmp2 = tmp * par[9];
  par[6] = par[i];
  par[i] = par[4] + tmp2 + par[10] * par[5] * -1.0;
  par[5] = par[i];
  par[4] = tmp2;
  par[i] += input;
  return par[7];
}