void mlVectorScaleTo(float s, float v[3], float r[3])
{
  int i;
  for (i = 0; i < 3; i++)
    r[i] = s * v[i];
}