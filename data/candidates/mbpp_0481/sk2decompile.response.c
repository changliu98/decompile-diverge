bool isSubsetSum(int set[], int n, int sum) {
  if (sum == 0) return true;
  if (n == 0) return false;
  bool res = false;
  if (set[n - 1] <= sum) res = isSubsetSum(set, n - 1, sum);
  return isSubsetSum(set, n - 1, sum) || res;
}