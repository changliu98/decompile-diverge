int f(int n)
{
  int i;
  int min;
  int temp;
  int temp2;
  if (n < 4)
    return n;
  min = n;
  for (i = 1; i <= n; i++)
  {
    temp = i * i;
    if (temp > n)
      break;
    temp2 = f(n - temp);
    if (temp2 + 1 < min)
      min = temp2 + 1;
    else
      min = min;
  }
  return min;
}