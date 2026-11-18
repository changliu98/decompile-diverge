int nchoosek(int n, int k)
{
  int ret = 0;
  if (n < k)
    return -1;
  ret += (n - k + 1)*(n - k + 2)/2;
  ret += (n - 2*k + 1)*(n - 2*k + 2)/2;
  return ret;
}