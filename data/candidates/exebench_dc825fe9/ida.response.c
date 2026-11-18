void __cdecl summary(int *arr, int len, double *pos_count, double *neg_count, double *zero_count)
{
  int i; // [rsp+0h] [rbp-38h]
  int zero_c; // [rsp+4h] [rbp-34h]
  int neg_c; // [rsp+8h] [rbp-30h]
  int pos_c; // [rsp+Ch] [rbp-2Ch]

  pos_c = 0;
  neg_c = 0;
  zero_c = 0;
  for ( i = 0; i < len; ++i )
  {
    if ( arr[i] <= 0 )
    {
      if ( arr[i] >= 0 )
        ++zero_c;
      else
        ++neg_c;
    }
    else
    {
      ++pos_c;
    }
  }
  *pos_count = (double)pos_c / (double)len;
  *neg_count = (double)neg_c / (double)len;
  *zero_count = (double)zero_c / (double)len;
}