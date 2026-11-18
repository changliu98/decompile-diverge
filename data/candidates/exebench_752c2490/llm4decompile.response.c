int valid(int *a, int n)
{
 int i;
 for (i = 0; i < n - 2; i++) {
  if (a[i] > 0) {
   a[i + 2] -= 3 * a[i];
   a[i + 1] -= 2 * a[i];
   a[i] = 0;
  } else if (a[i] < 0) {
   return 0;
  }
 }
 return a[n - 1] || !a[n - 2];
}