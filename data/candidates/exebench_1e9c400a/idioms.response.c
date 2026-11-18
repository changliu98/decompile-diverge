void myArrayDiv(float *in, float div, float *out)
{
  int i;
  for (i = 0; i < 5; i++)
    out[i] = in[i] / div;
}