void v_sub(float v[3], float w[3])
{
  unsigned int i;
  for (i = 0; i < 3; i++)
    v[i] = v[i] - w[i];
}