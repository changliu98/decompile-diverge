int maxSubarrayLength(int *a, int n)
{
 int maxsofar = -2147483648, maxendinghere = 0;
 int l = 0, r = 0, s = 0;
 for (r = 0; ; r++) {
  if (r >= n) break;
  maxendinghere += a[r];
  if (maxsofar < maxendinghere) {
   maxsofar = maxendinghere;
   l = s;
   r--;
  } else if (maxendinghere < 0) {
   maxendinghere = 0;
   s = r + 1;
  }
 }
 return r - l + 1;
}