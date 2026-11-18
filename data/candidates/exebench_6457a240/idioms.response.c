void peneira(int n, int a[])
{
  int i = 1;
  int j = 2;
  int tmp = a[i];
  while (j <= n)
  {
    if (j < n && a[j] < a[j + 1])
      j++;
    if (tmp >= a[j])
      break;
    a[i] = a[j];
    i = j;
    j = i * 2;
  }
  a[i] = tmp;
}