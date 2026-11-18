int get_str_len(char *str)
{
  int len = strlen(str);
  return (len + 1) * len / 2;
}