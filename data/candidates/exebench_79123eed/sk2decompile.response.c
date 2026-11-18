void quant_u_dec(int u, float *x, float xmin, float xmax, int q) {
  float dx;
  dx = (float)(xmax - xmin) / (float)(q - 1);
  *x = xmin + (float)u * dx;
  return;
}