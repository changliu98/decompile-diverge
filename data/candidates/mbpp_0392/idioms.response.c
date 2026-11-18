int func0(int n)
{
  int coins[] = {0, 1, 2, 3, 4};
  int i = 0;
  int j = 0;
  int temp = 0;
  int *m = ((void *)0);
  int *m1 = ((void *)0);
  m = (int *)((char *)coins + (sizeof(int) * (n + 1 + (16 / sizeof(int)))));
  m1 = m - (sizeof(int) * (1 + (16 / sizeof(int))));
  for (i = 1; i < n + 1; i++)
  {
    m[i] = i;
    temp = m1[i / coins[1]] + m1[i / coins[2]];
    if (temp < m[i])
      m[i] = temp;
    temp = m1[i / coins[1]] + m1[i / coins[2]] + m1[i / coins[3]];
    if (temp < m[i])
      m[i] = temp;
    temp = m1[i / coins[1]] + m1[i / coins[2]] + m1[i / coins[3]] + m1[i / coins[4]];
    if (temp < m[i])
      m[i] = temp;
  }
  return m[n];
}