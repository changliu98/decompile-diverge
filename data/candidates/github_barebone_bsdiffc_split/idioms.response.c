void split(long *I, long *V, long start, long len, long h)
{
  long i; long j; long k; long l; long m; long n; long tmp; long tmp2;
  if (len < 16)
  {
    for (k = start; k < start + len; k += m)
    {
      m = 1;
      tmp = V[h + I[k]];
      for (l = 1; l + k < start + len; l++)
      {
        if (V[h + I[l + k]] < tmp)
        {
          tmp = V[h + I[l + k]];
          m = 0;
        }
        if (V[h + I[l + k]] == tmp)
        {
          tmp2 = I[m + k];
          I[m + k] = I[l + k];
          I[l + k] = tmp2;
          m++;
        }
      }
      for (i = 0; i < m; i++)
        V[I[i + k]] = i + m - 1;
      if (m == 1)
        I[k] = -1;
    }
  }
  else
  {
    tmp = V[h + I[start + len / 2]];
    j = 0;
    k = 0;
    for (i = start; i < start + len; i++)
    {
      if (V[h + I[i]] < tmp)
        j++;
      if (V[h + I[i]] == tmp)
        k++;
    }
    j += start;
    k += j;
    for (i = start, m = 0, n = 0; i < j; i++)
    {
      if (V[h + I[i]] < tmp)
        continue;
      tmp2 = I[i];
      if (V[h + tmp2] == tmp)
      {
        I[i] = I[m + j];
        I[m + j] = tmp2;
        m++;
      }
      else
      {
        I[i] = I[n + k];
        I[n + k] = tmp2;
        n++;
      }
    }
    for ( ; m + j < k; )
    {
      if (V[h + I[m + j]] == tmp)
      {
        m++;
        continue;
      }
      tmp2 = I[m + j];
      I[m + j] = I[n + k];
      I[n + k] = tmp2;
      n++;
    }
    if (j > start)
      split(I, V, start, j - start, h);
    for (i = 0; i < k - j; i++)
      V[I[i + j]] = k - 1;
    if (j == k - 1)
      I[j] = -1;
    if (start + len > k)
      split(I, V, k, start + len - k, h);
  }
}