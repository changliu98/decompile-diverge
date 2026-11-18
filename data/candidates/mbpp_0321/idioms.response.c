char *func0(char *str)
{
  int len = strlen(str);
  int i = 0;
  int j = 1;
  int k = 0;
  for (i = j; i <= len; i++)
  {
    k += sprintf(&to_str_res[k], "%d", i);
  }
  for (i = len - 1; i > 0; i--)
  {
    k += sprintf(&to_str_res[k], "%d", i);
  }
  to_str_res[k] = '\0';
  return to_str_res;
}