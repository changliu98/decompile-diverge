int *func0(int n)
{
  int *out = (int*)malloc(sizeof(int)*n);
  int i;
  out[0] = n;
  for (i = 1; i < n; i++)
    out[i] = out[i-1] + 2;
  return out;
}