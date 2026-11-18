char *nodigit(char *str)
{
  int i = 0;
  int j = 0;
  int k = 0;
  char dig[1024];
  for (k = 0; str[k]; k++)
  {
    if (((*__ctype_b_loc ())[(int) ((str[k]))] & (unsigned short) _ISdigit))
    {
      dig[j++] = str[k];
    }
    else
    {
      func0_res[i++] = str[k];
    }
  }
  dig[j] = '\0';
  func0_res[i] = '\0';
  strcat(func0_res, dig);
  return (func0_res);
}