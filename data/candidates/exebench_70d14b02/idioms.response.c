void lib3ds_vector_max(float *max, float *v)
{
  int i;
  for (i = 0; i < 3; i++)
    if (v[i] > max[i])
      max[i] = v[i];
}