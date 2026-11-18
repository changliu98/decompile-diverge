void __cdecl numpar(double *param, int *len, int *out)
{
  int n = *len;
  if (n <= 0)
    return;

  // Allocate Variable Length Array (VLA) to store indices of duplicates
  int skip_indices[n];
  int skip_count = -1;
  double diff = 0.0;

  int i = -1;
  while (i < n - 1)
  {
    ++i;

    // Skip 'i' if it matches any previously found duplicate index
    for (int j = 0; j < skip_count; ++j)
    {
      if (i == skip_indices[j])
        ++i;
    }

    int k = i + 1;
    while (k < n)
    {
      // Skip 'k' if it matches any previously found duplicate index
      for (int j = 0; j < skip_count; ++j)
      {
        if (k == skip_indices[j])
          ++k;
      }

      // Compute absolute difference: diff = |param[i] - param[k]|
      diff = param[i] - param[k];
      if (diff < 0.0)
        diff = -diff;

      // If a duplicate is found, record its index and decrement the output counter
      if (diff == 0.0)
      {
        skip_indices[++skip_count] = k;
        --(*out);
      }
      ++k;
    }
  }
}