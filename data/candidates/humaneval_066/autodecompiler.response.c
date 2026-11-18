int func0(char *str)
{
  int i;
  int sum;

  sum = 0;
  i = 0;
  while (1)
    {
      if (str[i] == '\0')
 break;
      if ((str[i] >= 65) && (str[i] <= 90))
 sum += str[i];
      i++;
    }
  return (sum);
}