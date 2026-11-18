int *func0(int n)
{
  int *out = (int *)malloc(sizeof(int) * (n + 1));
  
  out[0] = 1;
  if (n == 0) {
    return out;
  }
  
  out[1] = 3;
  for (int i = 2; i <= n; ++i) {
    if (i % 2 != 0) {
      // For odd indices
      out[i] = (i + 1) / 2 + out[i - 2] + out[i - 1] + 1;
    } else {
      // For even indices
      out[i] = i / 2 + 1;
    }
  }
  
  return out;
}