float *__cdecl func0(const float *l, int count, int *out_count)
{
  float v3; // xmm0_4
  int v4; // ecx
  int i; // [rsp+Ch] [rbp-24h]
  float *out; // [rsp+10h] [rbp-20h]

  out = (float *)malloc(4LL * count);
  *out_count = 0;
  for ( i = 0; i < count; ++i )
  {
    if ( l[i] > 0.0 )
    {
      v3 = l[i];
      v4 = (*out_count)++;
      out[v4] = v3;
    }
  }
  return out;
}