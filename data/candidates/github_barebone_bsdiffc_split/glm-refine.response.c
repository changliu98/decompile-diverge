void __cdecl split(int64_t *I, int64_t *V, int64_t start, int64_t len, int64_t h)
{
  int64_t i, j, k, x, tmp;
  int64_t jj, kk, jja, kka, ja, ka;

  if (len >= 16)
  {
    // Choose pivot element
    x = V[h + I[len / 2 + start]];

    // Count elements less than pivot (jj) and equal to pivot (kk)
    jj = 0;
    kk = 0;
    for (i = start; i < len + start; ++i)
    {
      if (V[h + I[i]] < x)
        ++jj;
      if (V[h + I[i]] == x)
        ++kk;
    }

    // Determine boundaries for the partitions
    jja = jj + start;       // Start index of the 'equal' partition
    kka = kk + jja;         // End index of the 'equal' partition

    // 3-way partitioning: move elements less than 'x' to the left, and elements equal to 'x' to the middle
    i = start;
    ja = 0;
    ka = 0;
    while (i < jja)
    {
      if (V[h + I[i]] >= x)
      {
        tmp = I[i];
        if (V[h + tmp] == x)
        {
          I[i] = I[ja + jja];
          I[ja + jja] = tmp;
          ++ja;
        }
        else
        {
          I[i] = I[ka + kka];
          I[ka + kka] = tmp;
          ++ka;
        }
      }
      else
      {
        ++i;
      }
    }

    // Move remaining elements equal to 'x' into the middle partition
    while (ja + jja < kka)
    {
      if (V[h + I[ja + jja]] == x)
      {
        ++ja;
      }
      else
      {
        tmp = I[ja + jja];
        I[ja + jja] = I[ka + kka];
        I[ka + kka] = tmp;
        ++ka;
      }
    }

    // Recursively sort the 'less than' partition
    if (jja > start)
      split(I, V, start, jja - start, h);

    // Update rank array 'V' for the 'equal' partition
    for (i = 0; i < kka - jja; ++i)
      V[I[i + jja]] = kka - 1;

    // Mark singletons
    if (jja == kka - 1)
      I[jja] = -1;

    // Recursively sort the 'greater than' partition
    if (len + start > kka)
      split(I, V, kka, len + start - kka, h);
  }
  else
  {
    // Insertion sort for small segments
    for (k = start; k < len + start; k += j)
    {
      j = 1;
      x = V[h + I[k]];
      for (i = 1; i + k < len + start; ++i)
      {
        if (V[h + I[i + k]] < x)
        {
          x = V[h + I[i + k]];
          j = 0;
        }
        if (V[h + I[i + k]] == x)
        {
          tmp = I[j + k];
          I[j + k] = I[i + k];
          I[i + k] = tmp;
          ++j;
        }
      }
      for (i = 0; i < j; ++i)
        V[I[i + k]] = j + k - 1;

      if (j == 1)
        I[k] = -1;
    }
  }
}