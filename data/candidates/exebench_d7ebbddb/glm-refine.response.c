void __cdecl raw_relu_bulk_apply_function(int n, float *ptr)
{
  for (int i = 0; i < n; ++i)
  {
    // ReLU activation: f(x) = max(0, x)
    ptr[i] = ptr[i] > 0.0f ? ptr[i] : 0.0f;
  }
}