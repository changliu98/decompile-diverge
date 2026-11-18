int func0(int *arr, int n)
{
  int i;
  int flag = 0;
  for (i = 0; i < n; i++)
    if (arr[i] == 1) {
      flag = 1;
      break;
    }
  if (flag) {
    for (i = 0; i < n; i++)
      if (arr[i] < 1 || arr[i] > n)
        arr[i] = 1;
    for (i = 0; i < n; i++)
      arr[(arr[i] - 1) % n] += n;
    for (i = 0; i < n; i++)
      if (arr[i] <= n)
        return i + 1;
    return n + 1;
  } else
    return 1;
}