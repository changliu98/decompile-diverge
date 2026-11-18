void __cdecl func0(float *numbers, int size, float *out)
{
  float min_diff = 3.4028235e38f; // FLT_MAX
  float temp;
  int i, j;

  // Initialize with the first two elements
  *out = numbers[0];
  out[1] = numbers[1];

  // Find the pair of numbers with the smallest absolute difference
  for (i = 0; i < size; ++i)
  {
    for (j = i + 1; j < size; ++j)
    {
      float diff = fabsf(numbers[i] - numbers[j]);
      
      if (min_diff > diff)
      {
        min_diff = diff;
        *out = numbers[i];
        out[1] = numbers[j];
      }
    }
  }

  // Sort the output pair in ascending order
  if (*out > out[1])
  {
    temp = *out;
    *out = out[1];
    out[1] = temp;
  }
}