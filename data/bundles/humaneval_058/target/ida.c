int *__cdecl func0(int *l1, int size1, int *l2, int size2, int *out_size)
{
  int v5; // ecx
  int temp; // [rsp+8h] [rbp-48h]
  int exists_in_out; // [rsp+Ch] [rbp-44h]
  int m; // [rsp+10h] [rbp-40h]
  int j; // [rsp+14h] [rbp-3Ch]
  int ja; // [rsp+14h] [rbp-3Ch]
  int i; // [rsp+18h] [rbp-38h]
  int ia; // [rsp+18h] [rbp-38h]
  int k; // [rsp+1Ch] [rbp-34h]
  int *out; // [rsp+20h] [rbp-30h]

  out = (int *)malloc(4LL * size1);
  k = 0;
  for ( i = 0; i < size1; ++i )
  {
    exists_in_out = 0;
    for ( m = 0; m < k; ++m )
    {
      if ( out[m] == l1[i] )
      {
        exists_in_out = 1;
        break;
      }
    }
    if ( !exists_in_out )
    {
      for ( j = 0; j < size2; ++j )
      {
        if ( l1[i] == l2[j] )
        {
          v5 = k++;
          out[v5] = l1[i];
          break;
        }
      }
    }
  }
  for ( ia = 0; ia < k - 1; ++ia )
  {
    for ( ja = 0; ja < k - ia - 1; ++ja )
    {
      if ( out[ja] > out[ja + 1] )
      {
        temp = out[ja];
        out[ja] = out[ja + 1];
        out[ja + 1] = temp;
      }
    }
  }
  *out_size = k;
  return out;
}