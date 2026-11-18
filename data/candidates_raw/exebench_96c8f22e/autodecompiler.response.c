void compute(float *x, float w, float s)
{
  long i;
  for(i = 0; ; i++)
    if (i < 7) {
      x[0] = w * (x[0] + x[1] + x[2] - x[3]);
      x[1] = w * (x[0] + x[1] - x[2] + x[3]);
      x[2] = w * (x[0] - x[1] + x[2] + x[3]);
      x[3] = (x[0] ^ (float)0x80000000U) + x[1] + x[2] + x[3] / s;
    } else {
      return;
    }
}