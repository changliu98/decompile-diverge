int get_sum(int *a, int *b, int n)
{
 sort(a, n);
 sort(b, n);
 int sum = 0;
 int i;
 for (i = 0; i < n; i++)
  sum += abs(a[i]-b[i]);
 return sum;
}