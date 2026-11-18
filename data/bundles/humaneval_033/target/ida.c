void __cdecl func0(int *l, int size, int *out)
{
  int v3; // edx
  int temp; // [rsp+Ch] [rbp-34h]
  int min_idx; // [rsp+10h] [rbp-30h]
  int third_size; // [rsp+14h] [rbp-2Ch]
  int k; // [rsp+18h] [rbp-28h]
  int i; // [rsp+1Ch] [rbp-24h]
  int ia; // [rsp+1Ch] [rbp-24h]
  int ib; // [rsp+1Ch] [rbp-24h]
  int *third; // [rsp+20h] [rbp-20h]

  third = (int *)malloc(4LL * (size / 3 + 1));
  third_size = 0;
  for ( i = 0; 3 * i < size; ++i )
  {
    third[i] = l[3 * i];
    ++third_size;
  }
  for ( ia = 0; ia < third_size - 1; ++ia )
  {
    min_idx = ia;
    for ( k = ia + 1; k < third_size; ++k )
    {
      if ( third[k] < third[min_idx] )
        min_idx = k;
    }
    if ( min_idx != ia )
    {
      temp = third[ia];
      third[ia] = third[min_idx];
      third[min_idx] = temp;
    }
  }
  for ( ib = 0; ib < size; ++ib )
  {
    if ( ib % 3 )
      v3 = l[ib];
    else
      v3 = third[ib / 3];
    out[ib] = v3;
  }
  free(third);
}