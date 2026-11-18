int find_peak(int a[], int n)
{
  return find_peak_util(a, 0, n - 1, n);
}