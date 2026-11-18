int plot_digit_wierd(char digit, float x, float y, float hgt, float h, float *vx, float *vy)
{
  int i; int ib; int ie; int n = 0;
  float rs; float cs; float hl; float he;
  if (digit < '0' || digit > '9')
    return 0;
  ib = plot_digit_wierd_lt[(int)(digit - '0')];
  ie = plot_digit_wierd_lt[(int)(digit - '0') + 1] - 1;
  for (i = ib; i <= ie; i++) {
    hl = hgt * (plot_digit_wierd_lb[i] / 10);
    he = h * (plot_digit_wierd_lb[i] % 10);
    if (i != ib) {
      vx[n] = rs;
      vy[n] = cs;
      n++;
      vx[n] = x - hl;
      vy[n] = y - he;
      n++;
    }
    rs = x - hl;
    cs = y - he;
  }
  return n;
}