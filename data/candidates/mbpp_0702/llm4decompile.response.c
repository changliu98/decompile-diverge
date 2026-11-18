int func0(char **arr, int n, int k)
{
 int i, j, ans = n - 1;
 qsort(arr, (size_t)n, sizeof(char *), PTR_strcmp);
 for (i = 0; i < n; i++) {
  j = find_ind(arr[i], i, n, k, arr);
  if (j != -1)
   ans = ((ans) < (n - (j - i + 1)) ? (ans) : (n - (j - i + 1)));
 }
 return ans;
}