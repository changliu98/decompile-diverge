char *convert_set_sign(char *str, int *sign)
{
  *sign = 1;
  if (str == ((void *)0))
    return str;
  if (*str == '+')
    {
      *sign = 1;
      return str + 1;
    }
  if (*str == '-')
    {
      *sign = -1;
      return str + 1;
    }
  return str;
}