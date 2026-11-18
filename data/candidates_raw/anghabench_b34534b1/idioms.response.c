char *get_str(char *str, int *base)
{
  if (*str == '0')
  {
    switch (str[1])
    {
      case 'n':
      case 't':
        *base = 10;
        str += 2;
        break;
      case 'o':
        *base = 8;
        str += 2;
        break;
      case 'x':
        *base = 16;
        str += 2;
        break;
      default:
        *base = 10;
        str += 1;
        break;
    }
  }
  else
  {
    *base = 10;
    return str;
  }
  return str;
}