int func0(int a[], int n)
{
  int min = a[0];
  int max = a[0];
  int i = 0;
  for (i = 1; i < n; i++) {
    if (a[i] < min)
      min = a[i];
    if (a[i] > max)
      max = a[i];
  }
  return (max - min);
}