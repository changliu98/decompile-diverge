int func0(int n, int a, int b, int c)
{
 int dp[n + 10];
 for (int i = 0; i < n + 10; i++)
  dp[i] = -1;
 dp[0] = 0;
 for (int i = 0; i <= n; i++) {
  if (dp[i] != -1) {
   if (i + a <= n)
    dp[i + a] = ((dp[i + a]) > (dp[i] + 1) ? (dp[i] + 1) : (dp[i + a]));
   if (i + b <= n)
    dp[i + b] = ((dp[i + b]) > (dp[i] + 1) ? (dp[i] + 1) : (dp[i + b]));
   if (i + c <= n)
    dp[i + c] = ((dp[i + c]) > (dp[i] + 1) ? (dp[i] + 1) : (dp[i + c]));
  }
 }
 return dp[n];
}