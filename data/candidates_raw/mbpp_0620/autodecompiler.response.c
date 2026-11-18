int lis(int arr[], int n)
{
   int dp[n], ans, i, j, mxm;

   dp[n-1] = 1;
   for(i = n-2 ; i >= 0 ; --i)
   {
      mxm = 0;
      for(j = i+1 ; j < n ; ++j)
         if(arr[j]%arr[i] == 0 || arr[i]%arr[j] == 0)
            mxm = ((mxm) > (dp[j]) ? (mxm) : (dp[j]));
      dp[i] = mxm + 1;
   }

   ans = dp[0];
   for(i = 1 ; i < n ; ++i)
      ans = ((ans) > (dp[i]) ? (ans) : (dp[i]));

   return ans;
}