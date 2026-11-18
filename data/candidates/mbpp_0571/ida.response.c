int __cdecl func0(int *arr, int N, int K)
{
  int v4; // [rsp+8h] [rbp-28h]
  int v5; // [rsp+Ch] [rbp-24h]
  int result; // [rsp+10h] [rbp-20h]
  int i; // [rsp+14h] [rbp-1Ch]
  int *dp; // [rsp+18h] [rbp-18h]

  qsort(arr, N, 4uLL, (__compar_fn_t)cmpfunc);
  dp = (int *)malloc(4LL * N);
  *dp = 0;
  for ( i = 1; i < N; ++i )
  {
    dp[i] = dp[i - 1];
    if ( arr[i] - arr[i - 1] < K )
    {
      if ( i < 2 )
      {
        if ( dp[i] <= arr[i - 1] + arr[i] )
          v4 = arr[i - 1] + arr[i];
        else
          v4 = dp[i];
        dp[i] = v4;
      }
      else
      {
        if ( dp[i] <= arr[i - 1] + arr[i] + dp[i - 2] )
          v5 = arr[i - 1] + arr[i] + dp[i - 2];
        else
          v5 = dp[i];
        dp[i] = v5;
      }
    }
  }
  result = dp[N - 1];
  free(dp);
  return result;
}