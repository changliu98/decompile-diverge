int __cdecl find_max_idx(const float *f)
{
  float max_val = 0.0f;
  int max_idx = -1;

  // Find the maximum value and its index in the 16-element array
  for (int i = 0; i < 16; ++i)
  {
    if (f[i] > max_val)
    {
      max_val = f[i];
      max_idx = i;
    }
  }

  // If no positive value was found, return -1
  if (max_idx == -1)
    return -1;

  // Ensure the maximum value is significantly larger than all other elements
  for (int i = 0; i < 16; ++i)
  {
    if (i != max_idx)
    {
      if (f[i] > max_val * 0.1f)
        return -1;
    }
  }

  return max_idx;
}