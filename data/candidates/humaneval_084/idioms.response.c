char *func0(int n)
{
  char *str;
  int sum;
  int i;
  int index;
  char temp;
  int num = n;
  str = (char *)malloc(sizeof(char) * 33);
  sprintf(str, "%d", num);
  sum = 0;
  for (i = 0; str[i]; i++)
    sum += str[i] - '0';
  index = 0;
  if (sum == 0)
  {
    index = 1;
    str[index - 1] = '0';
  }
  else
  {
    while (sum > 0)
    {
      str[index++] = (sum % 2) + '0';
      sum /= 2;
    }
  }
  str[index] = '\0';
  for (i = 0; i < index / 2; i++)
  {
    temp = str[i];
    str[i] = str[index - i - 1];
    str[index - i - 1] = temp;
  }
  return str;
}