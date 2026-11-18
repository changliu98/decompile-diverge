int itoa(char *str, int num)
{
  int i; int j; int k;
  if (num == 0)
  {
    str[0] = '0';
    str[1] = '\0';
    return 2;
  }
  for (i = 0, k = 1; num % k != num; i++)
  {
    k *= 10;
  }
  if (num < 0)
  {
    i++;
  }
  for (k = 1, j = i - 1; j >= 0; j--)
  {
    str[j] = (num - (num % k)) / k % 10 + '0';
    k *= 10;
  }
  if (num < 0)
  {
    str[0] = '-';
  }
  str[i] = '\0';
  return i;
}