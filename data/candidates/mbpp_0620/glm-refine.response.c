int __cdecl func0(int *a, int n)
{
  // Allocate a Variable Length Array (VLA) equivalent to the stack allocation
  int *v3 = (int *)malloc(4 * n);
  if (!v3) return 0; // Safety check for malloc failure

  v3[n - 1] = 1;
  for (int i = n - 2; i >= 0; --i)
  {
    int mxm = 0;
    for (int j = i + 1; j < n; ++j)
    {
      if ((!(a[j] % a[i]) || !(a[i] % a[j])) && mxm < v3[j])
        mxm = v3[j];
    }
    v3[i] = mxm + 1;
  }

  int max_val = v3[0];
  for (int i_0 = 1; i_0 < n; ++i_0)
  {
    if (max_val < v3[i_0])
      max_val = v3[i_0];
  }

  free(v3);
  return max_val;
}