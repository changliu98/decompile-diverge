void raw_relu_bulk_apply_function(int n, float *a)
{
  int i;
  for (i = 0; i < n; i++)
    a[i] = (a[i] > 0.0) ? a[i] : 0.0;
}