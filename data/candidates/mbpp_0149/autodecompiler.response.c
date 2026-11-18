int func0(int arr[], int n)
{
   int dp[n], ans, i = 0, j = 0;

   for(i = 0 ; i < n ; ++i)
      dp[i] = 1;

   for(i = 0 ; i < n ; ++i)
      for(j = 0 ; j < i ; j++)
         if(arr[i] == arr[j] + 1 || arr[i] == arr[j] - 1)

            if(dp[i] < dp[j] + 1)
               dp[i] = dp[j] + 1;


   ans = 1;
   for(i = 0 ; i < n ; ++i)
      if(ans < dp[i])
         ans = dp[i];

   return ans;
}