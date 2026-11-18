void scale(float *v, float k)
{
  int i;
  for (i = 0; i < 4; i++)
    v[i] *= k;
}