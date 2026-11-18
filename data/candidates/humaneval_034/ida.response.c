int *__cdecl func0(int *l, int size, int *out_size)
{
  int v3; // ecx
  int temp; // [rsp+Ch] [rbp-34h]
  int j; // [rsp+10h] [rbp-30h]
  int ja; // [rsp+10h] [rbp-30h]
  int i; // [rsp+14h] [rbp-2Ch]
  int ia; // [rsp+14h] [rbp-2Ch]
  int out_count; // [rsp+18h] [rbp-28h]
  int found; // [rsp+1Ch] [rbp-24h]
  int *out; // [rsp+20h] [rbp-20h]

  out = (int *)malloc(4LL * size);
  out_count = 0;
  for ( i = 0; i < size; ++i )
  {
    found = 0;
    for ( j = 0; j < out_count; ++j )
    {
      if ( l[i] == out[j] )
      {
        found = 1;
        break;
      }
    }
    if ( !found )
    {
      v3 = out_count++;
      out[v3] = l[i];
    }
  }
  for ( ia = 0; ia < out_count - 1; ++ia )
  {
    for ( ja = ia + 1; ja < out_count; ++ja )
    {
      if ( out[ia] > out[ja] )
      {
        temp = out[ia];
        out[ia] = out[ja];
        out[ja] = temp;
      }
    }
  }
  *out_size = out_count;
  return out;
}