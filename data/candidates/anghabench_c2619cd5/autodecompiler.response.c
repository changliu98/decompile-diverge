int binary_search(int x[], int n, int t)
{
 int m, l, u;

 l = 0;
 u = n-1;
 while (l <= u) {
  m = l + (u-l)/2;
  if (x[m] > t)
   u = m-1;
  else if (x[m] < t)
   l = m+1;
  else
   return m;
 }
 return -1;
}