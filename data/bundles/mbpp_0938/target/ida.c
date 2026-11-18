void __cdecl func0(int *A, int *B, int *C, int p, int q, int r, int *res)
{
  int v7; // [rsp+0h] [rbp-64h]
  int v8; // [rsp+4h] [rbp-60h]
  int v9; // [rsp+8h] [rbp-5Ch]
  int v10; // [rsp+Ch] [rbp-58h]
  int v11; // [rsp+10h] [rbp-54h]
  int v12; // [rsp+14h] [rbp-50h]
  bool v13; // [rsp+1Bh] [rbp-49h]
  int k; // [rsp+24h] [rbp-40h]
  int j; // [rsp+28h] [rbp-3Ch]
  int i; // [rsp+2Ch] [rbp-38h]
  int res_k; // [rsp+30h] [rbp-34h]
  int res_j; // [rsp+34h] [rbp-30h]
  int res_i; // [rsp+38h] [rbp-2Ch]
  int diff; // [rsp+3Ch] [rbp-28h]

  diff = 0x7FFFFFFF;
  res_i = 0;
  res_j = 0;
  res_k = 0;
  i = 0;
  j = 0;
  k = 0;
  while ( 1 )
  {
    v13 = 0;
    if ( i < p )
    {
      v13 = 0;
      if ( j < q )
        v13 = k < r;
    }
    if ( !v13 )
      break;
    if ( A[i] >= B[j] )
    {
      v10 = B[j] >= C[k] ? C[k] : B[j];
      v11 = v10;
    }
    else
    {
      v12 = A[i] >= C[k] ? C[k] : A[i];
      v11 = v12;
    }
    if ( A[i] <= B[j] )
    {
      v7 = B[j] <= C[k] ? C[k] : B[j];
      v8 = v7;
    }
    else
    {
      v9 = A[i] <= C[k] ? C[k] : A[i];
      v8 = v9;
    }
    if ( v8 - v11 < diff )
    {
      res_i = i;
      res_j = j;
      res_k = k;
      diff = v8 - v11;
    }
    if ( !diff )
      break;
    if ( A[i] == v11 )
    {
      ++i;
    }
    else if ( B[j] == v11 )
    {
      ++j;
    }
    else
    {
      ++k;
    }
  }
  *res = A[res_i];
  res[1] = B[res_j];
  res[2] = C[res_k];
}