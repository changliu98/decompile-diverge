unsigned __int64 __cdecl func0(int n)
{
  int i_1; // [rsp+4h] [rbp-2Ch]
  unsigned __int64 result; // [rsp+8h] [rbp-28h]
  int j_0; // [rsp+10h] [rbp-20h]
  int i_0; // [rsp+14h] [rbp-1Ch]
  int j; // [rsp+18h] [rbp-18h]
  int i; // [rsp+1Ch] [rbp-14h]
  unsigned __int64 **bell; // [rsp+20h] [rbp-10h]

  bell = (unsigned __int64 **)malloc(8LL * (n + 1));
  for ( i = 0; i <= n; ++i )
  {
    bell[i] = (unsigned __int64 *)malloc(8LL * (n + 1));
    for ( j = 0; j <= n; ++j )
      bell[i][j] = 0LL;
  }
  **bell = 1LL;
  for ( i_0 = 1; i_0 <= n; ++i_0 )
  {
    *bell[i_0] = bell[i_0 - 1][i_0 - 1];
    for ( j_0 = 1; j_0 <= i_0; ++j_0 )
      bell[i_0][j_0] = bell[i_0][j_0 - 1] + bell[i_0 - 1][j_0 - 1];
  }
  result = *bell[n];
  for ( i_1 = 0; i_1 <= n; ++i_1 )
    free(bell[i_1]);
  free(bell);
  return result;
}