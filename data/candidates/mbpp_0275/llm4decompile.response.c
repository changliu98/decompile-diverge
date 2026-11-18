int func0(int *a, int n, int m)
{
 int i;
 int maxx;
 int index;

 for (i = 0; i < n; i++)
  a[i] = a[i] / m + (a[i] % m != 0);

 maxx = -1;
 index = -1;
 for (i = n - 1; i >= 0; i--) {
  if (a[i] > maxx) {
   maxx = a[i];
   index = i;
  }
 }

 return index + 1;
}