int func0(int arr[], int n)
{
 int ans = 0;
 for (int i = 0; i < n; i++)
  for (int j = i + 1; j < n; j++)
   ans += arr[i] ^ arr[j];
 return ans;
}