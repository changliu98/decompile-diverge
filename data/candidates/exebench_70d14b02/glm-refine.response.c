void __cdecl lib3ds_vector_max(float *c, float *a)
{
  // Iterate through the 3 dimensions (X, Y, Z) of the vectors
  for (int i = 0; i < 3; ++i)
  {
    // Perform a component-wise maximum operation
    if (a[i] > c[i])
      c[i] = a[i];
  }
}