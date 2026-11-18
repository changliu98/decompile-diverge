int findMin(int *a, int n)
{
 int *freq = (int *)calloc(n + 1, sizeof(int));
 int min = -1;
 int i = 0;
 while (1) {
  if (i >= n) {
   break;
  }
  freq[a[i]]++;
  if (freq[a[i]] >= a[i] && a[i] > min) {
   min = a[i];
  }
  i++;
 }
 free(freq);
 return min;
}