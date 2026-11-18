int __cdecl func0(int *a, int n, int x)
{
  int l = 0;
  int mid;

  while (l < n)
  {
    mid = (l + n) / 2;
    if (a[mid] >= x)
      n = mid;
    else
      l = mid + 1;
  }
  
  return l;
}