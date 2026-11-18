int func0(int *a, int n, int x)
{
 int l = 0, r = n;
 while (l < r) {
  int mid = (l + r) / 2;
  if (a[mid] < x)
   l = mid + 1;
  else
   r = mid;
 }
 return l;
}