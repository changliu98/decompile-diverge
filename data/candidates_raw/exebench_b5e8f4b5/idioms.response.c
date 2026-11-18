char *get_num_str(char *str, int *base)
{
  *base = 10;
  if (str == ((void *)0))
    return str;
  if (str[0] == '0') {
    str++;
    if (str[0] == 'x' || str[0] == 'X') {
      *base = 16;
      str++;
    }
  }
  return str;
}