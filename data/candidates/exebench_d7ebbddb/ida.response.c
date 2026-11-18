void __cdecl raw_relu_bulk_apply_function(int n, float *ptr)
{
  float v2; // xmm0_4
  double v3; // [rsp+0h] [rbp-20h]
  int i; // [rsp+Ch] [rbp-14h]

  for ( i = 0; i < n; ++i )
  {
    if ( ptr[i] <= 0.0 )
      v3 = 0.0;
    else
      v3 = ptr[i];
    v2 = v3;
    ptr[i] = v2;
  }
}