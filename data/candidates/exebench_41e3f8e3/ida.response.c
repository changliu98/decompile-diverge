void __cdecl table_norm(double *data3_nn, int data3_len, double *data2_nn, int data2_len, long *result, int result_len)
{
  int j; // [rsp+0h] [rbp-34h]
  int i; // [rsp+4h] [rbp-30h]
  int ia; // [rsp+4h] [rbp-30h]

  for ( i = 0; i < data2_len; ++i )
  {
    for ( j = 0; j < data3_len; ++j )
    {
      if ( data3_nn[j] > data2_nn[i] )
        ++result[j];
    }
  }
  for ( ia = 0; ia < result_len; ++ia )
  {
    if ( !result[ia] )
      result[ia] = 1LL;
  }
}