int hex_to_int(char *str, int *res)
{
  int i;
  *res = 0;
  for (i = 0; i < 8; i++)
  {
    if (str[i] >= '0' && str[i] <= '9')
    {
      *res = *res * 16 + str[i] - '0';
    }
    else if (str[i] >= 'a' && str[i] <= 'f')
    {
      *res = *res * 16 + str[i] - 'a' + 10;
    }
    else
    {
      return 0;
    }
  }
  return 1;
}