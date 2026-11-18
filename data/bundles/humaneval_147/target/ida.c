int __cdecl func0(int n)
{
  __int64 v1; // rcx
  __int64 v2; // rcx
  int i_3; // [rsp+14h] [rbp-4Ch]
  int result; // [rsp+18h] [rbp-48h]
  int j_2; // [rsp+1Ch] [rbp-44h]
  int i_2; // [rsp+20h] [rbp-40h]
  int j_1; // [rsp+24h] [rbp-3Ch]
  int j_0; // [rsp+28h] [rbp-38h]
  int i_1; // [rsp+2Ch] [rbp-34h]
  int times; // [rsp+30h] [rbp-30h]
  int j; // [rsp+34h] [rbp-2Ch]
  int i_0; // [rsp+38h] [rbp-28h]
  int i; // [rsp+3Ch] [rbp-24h]
  int **sum2; // [rsp+40h] [rbp-20h]
  int **sum; // [rsp+48h] [rbp-18h]
  int *a; // [rsp+50h] [rbp-10h]

  a = (int *)malloc(4LL * n);
  sum = (int **)malloc(8LL * (n + 1));
  sum2 = (int **)malloc(8LL * (n + 1));
  for ( i = 0; i <= n; ++i )
  {
    sum[i] = (int *)calloc(3uLL, 4uLL);
    sum2[i] = (int *)calloc(3uLL, 4uLL);
  }
  (*sum)[2] = 0;
  (*sum)[1] = 0;
  **sum = 0;
  (*sum2)[2] = 0;
  (*sum2)[1] = 0;
  **sum2 = 0;
  for ( i_0 = 1; i_0 <= n; ++i_0 )
  {
    a[i_0 - 1] = (i_0 * i_0 - i_0 + 1) % 3;
    for ( j = 0; j < 3; ++j )
      sum[i_0][j] = sum[i_0 - 1][j];
    v1 = a[i_0 - 1];
    ++sum[i_0][v1];
  }
  for ( times = 1; times < 3; ++times )
  {
    for ( i_1 = 1; i_1 <= n; ++i_1 )
    {
      for ( j_0 = 0; j_0 < 3; ++j_0 )
        sum2[i_1][j_0] = sum2[i_1 - 1][j_0];
      if ( i_1 >= 1 )
      {
        for ( j_1 = 0; j_1 <= 2; ++j_1 )
        {
          v2 = (j_1 + a[i_1 - 1]) % 3;
          sum2[i_1][v2] += sum[i_1 - 1][j_1];
        }
      }
    }
    for ( i_2 = 0; i_2 <= n; ++i_2 )
    {
      for ( j_2 = 0; j_2 < 3; ++j_2 )
      {
        sum[i_2][j_2] = sum2[i_2][j_2];
        sum2[i_2][j_2] = 0;
      }
    }
  }
  result = *sum[n];
  for ( i_3 = 0; i_3 <= n; ++i_3 )
  {
    free(sum[i_3]);
    free(sum2[i_3]);
  }
  free(sum);
  free(sum2);
  free(a);
  return result;
}