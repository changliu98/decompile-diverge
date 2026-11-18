int func0(int a[], int n)
{
  int i;
  int increasing = 1;
  int decreasing = 1;
  for (i = 0; i < n - 1; i++) {
    if (a[i] > a[i + 1])
      increasing = 0;
    if (a[i] < a[i + 1])
      decreasing = 0;
  }
  if (increasing)
    return 1;
  return decreasing;
}