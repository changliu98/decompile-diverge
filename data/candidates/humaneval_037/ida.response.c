void __cdecl func0(float *l, int size, float *out)
{
  int v3; // ecx
  float v4; // xmm0_4
  float temp; // [rsp+10h] [rbp-30h]
  int even_count; // [rsp+14h] [rbp-2Ch]
  int j; // [rsp+18h] [rbp-28h]
  int i; // [rsp+1Ch] [rbp-24h]
  int ia; // [rsp+1Ch] [rbp-24h]
  int ib; // [rsp+1Ch] [rbp-24h]
  float *even; // [rsp+20h] [rbp-20h]

  even = (float *)malloc(4LL * (size / 2 + 1));
  even_count = 0;
  for ( i = 0; i < size; i += 2 )
  {
    v3 = even_count++;
    even[v3] = l[i];
  }
  for ( ia = 0; ia < even_count - 1; ++ia )
  {
    for ( j = 0; j < even_count - ia - 1; ++j )
    {
      if ( even[j] > even[j + 1] )
      {
        temp = even[j];
        even[j] = even[j + 1];
        even[j + 1] = temp;
      }
    }
  }
  for ( ib = 0; ib < size; ++ib )
  {
    if ( ib % 2 )
      v4 = l[ib];
    else
      v4 = even[ib / 2];
    out[ib] = v4;
  }
  free(even);
}