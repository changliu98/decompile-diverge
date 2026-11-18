char *make_upper_case(char *str)
{
  char *tmp;

  tmp = str;
  while (*tmp != '\0')
  {
    if (*tmp == '-')
      *tmp = '_';
    else if (*tmp >= 'a' && *tmp <= 'z')
      *tmp -= 32;
    else if (*tmp < 'A' || *tmp > 'Z')
    {
      *str = '\0';
      break;
    }
    tmp++;
  }
  return (str);
}