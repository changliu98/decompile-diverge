void d2f(float *out, double *in, unsigned long sampleCount)
{
  if (out == ((void *)0))
    return;
  if (in == ((void *)0))
    return;
  for (unsigned long i = 0; i < sampleCount; i++)
    out++[i] = in[i];
}