int lis(int arr[], int n)
{
   int dp[n], ans, i, j;

   for(i = 0; i < n; ++i)
      dp[i] = 1;

   for(i = 1; i < n; ++i)
      for(j = 0; j < i; ++j)
         if(arr[i] > arr[j] && dp[i] < dp[j] + 1)
            dp[i] = dp[j] + 1;

   ans = 0;
   for(i = 0; i < n; ++i)
      if(ans < dp[i])
         ans = dp[i];

   return ans;
}