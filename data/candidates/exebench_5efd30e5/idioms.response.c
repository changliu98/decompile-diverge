int stringToInt(int *val, char *str)
{
  *val = 0;
  while (*str)
    {
      if (*str < '0' || *str > '9')
        return (-1);
      *val = *val * 10 + *str - '0';
      str++;
    }
  return (0);
}