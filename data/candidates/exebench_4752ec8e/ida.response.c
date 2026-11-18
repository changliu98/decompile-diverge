void __cdecl f1(int n, float a, float *x, float *y)
{
  int i; // [rsp+0h] [rbp-1Ch]

  for ( i = 0; i < n; ++i )
    y[i] = (float)(a * x[i]) + y[i];
}