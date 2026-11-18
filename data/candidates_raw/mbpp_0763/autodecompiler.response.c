int findMin(int *a, int n)
{
 int i, j;
 for (i = 0; i < n-1; ++i) {
  for (j = 0; j < n-i-1; ++j) {
   if (a[j] > a[j+1]) {
    int tmp = a[j];
    a[j] = a[j+1];
    a[j+1] = tmp;
   }
  }
 }

 int min = 0x7fffffff;
 for (i = 0; i < n-1; ++i) {
  if (min > a[i+1] - a[i])
   min = a[i+1] - a[i];
 }

 return min;
}