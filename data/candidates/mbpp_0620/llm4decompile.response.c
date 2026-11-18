int func0(int *a, int n)
{
 int dp[n];
 dp[n-1] = 1;
 int i, j;
 for (i = n-2; i >= 0; i--) {
  int mxm = 0;
  for (j = i+1; j < n; j++) {
   if (a[j] % a[i] == 0 || a[i] % a[j] == 0) {
    mxm = mxm > dp[j] ? mxm : dp[j];
   }
  }
  dp[i] = mxm + 1;
 }
 int ans = dp[0];
 for (i = 1; i < n; i++) {
  ans = ans > dp[i] ? ans : dp[i];
 }
 return ans;
}